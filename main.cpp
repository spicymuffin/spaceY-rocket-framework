/**
 * @file main.cpp
 * @author luigi (luigicussigh59@gmail.com)
 * @brief spaceY's rocket control software
 * @version 1.1
 * @date 2023-11-20
 *
 * @copyright lol someone should pay me for this
 *
 *
 * use cmake to build this crap
 **/

// param
#include "debug_param.h"
#include "param.h"

// constants
#include "constants.h"

// base classes
#include "base_class/RocketModule.h"

// systems
#include "system/Clock.h"
#include "system/CommunicationSystem.h"
#include "system/FlightLogger.h"
#include "system/RocketState.h"

// hardware controllers
#include "hardware_controller/HardwareController_fuelcelligniter.h"
#include "hardware_controller/HardwareController_mpu6050.h"
#include "hardware_controller/HardwareController_picoonboardled.h"
#include "hardware_controller/HardwareController_servotype0.h"
#include "hardware_controller/HardwareController_usbfilesystem.h"

// actuators
#include "actuator/OnboardLed.h"
#include "actuator/TextDataSaver.h"
#include "actuator/KinematicDataProcessor.h"

// sensors
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"

// pico sdk
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

// util
#include "util/CircularBuffer.h"

// constants
#define TICK_LENGTH_MICROSECONDS MICROSECONDS_PER_SECOND / REFRESH_RATE
#define TICK_REMINDER_MICROSECONDS MICROSECONDS_PER_SECOND % REFRESH_RATE

// this is all unusuble unless someone makes the USB thing work ;-;
// const string FLIGHT_LOGS_DIRECTORY = "/data/flight logs";
// const string IMU_LOGS_DIRECTORY = "/data/IMU logs";

// const string COMMUNICATION_PROTOCOL_PATH = "/communication_protocols/mainprotocol.json";
// tick of rocket
unsigned int tick = 0;

// current tick's start's timestamp
uint32_t current_tick_ts = 0; // TODO: change to longs
// next tick's start's timestamp
uint32_t next_tick_ts = 0;

RocketModule *rmtable[RM_TABLE_LEN];
HardwareController *hctable[HC_TABLE_LEN];

int main(int argc, char *argv[])
{
#if DBGMSG_INITIALIZATION
    printf("intitializing...\n");
#endif

    for (int i = 0; i < RM_TABLE_LEN; i++)
    {
        rmtable[i] = nullptr;
    }

    for (int i = 0; i < HC_TABLE_LEN; i++)
    {
        hctable[i] = nullptr;
    }

#pragma region initialize rocket systems

    // init clock
    Clock clock = Clock();

#if DBGMSG_INITIALIZATION
    printf("system clock initialized.\n");
    printf("TICK_LENGTH_MICROSECONDS: %zu\n", TICK_LENGTH_MICROSECONDS);
    printf("TICK_REMINDER_MICROSECONDS: %zu\n", TICK_REMINDER_MICROSECONDS);
#endif

    /// TODO: fix flight log
    // initialize flight log
    // FlightLogger flightLog = FlightLogger("main flight log", cur_dir + FLIGHT_LOGS_DIRECTORY, "flight_log");
    // printf("%s initialized.\n", flightLog.get_name());

#pragma endregion

#pragma region initialize rocket modules part one

    KinematicDataProcessor kdp = KinematicDataProcessor("main_kdp", 1, &clock);
    rmtable[0] = &kdp;

#pragma endregion

#pragma region initialize hardware

    HardwareController_usbfilesystem HC_usbfilesystem = HardwareController_usbfilesystem("usbfilesystem", -1);
    HardwareController_picoonboardled HC_picoonboardled = HardwareController_picoonboardled("picoonboardled", -1);

    CircularBuffer<VectorInt16> *mpu6050_accelerometer_subscribers[] = {kdp.get_accelerometer_buffer_ref()};
    CircularBuffer<VectorInt16> *mpu6050_gyroscope_subscribers[] = {kdp.get_gyroscope_buffer_ref()};
    CircularBuffer<Quaternion> *mpu6050_orientation_subscribers[] = {kdp.get_orientation_buffer_ref()};

    HardwareController_mpu6050 HC_mpu6050 = HardwareController_mpu6050(
        "mpu6050",
        1,
        i2c_default,
        400 * 1000,
        mpu6050_accelerometer_subscribers,
        mpu6050_gyroscope_subscribers,
        mpu6050_orientation_subscribers,
        1,
        1,
        1);

    hctable[0] = &HC_usbfilesystem;
    hctable[1] = &HC_picoonboardled;
    hctable[2] = &HC_mpu6050;

#pragma endregion

#pragma region initialize modules

    OnboardLed led = OnboardLed("onboard_led",
                                4,
                                &HC_picoonboardled);
    rmtable[1] = &led;

    TextDataSaver kinem_data_tds = TextDataSaver("kinem_data_tds",
                                                 -1,
                                                 "",
                                                 "",
                                                 &HC_usbfilesystem);
    rmtable[2] = &kinem_data_tds;

    Accelerometer accelerometer = Accelerometer("main_accm",
                                                -1,
                                                nullptr,
                                                &clock,
                                                &HC_mpu6050);
    rmtable[3] = &accelerometer;

#pragma endregion

#pragma region intialize communication systems

    // vector<RocketModule *> mainCommuniationSystem_Modules = {};
    // init main Communication System
    // CommunicationSystem mainCommunicationSystem = CommunicationSystem("main communication system", 10, mainCommuniationSystem_Modules, cur_dir + COMMUNICATION_PROTOCOL_PATH);

#pragma endregion

    current_tick_ts = clock.get_new_ts();
    next_tick_ts = current_tick_ts;

    while (ENDLESS ? true : tick <= REFRESH_RATE * TEST_DURATION - 1)
    {
        // record this tick's start's timestamp
        current_tick_ts = clock.get_new_ts();

        // calculate when next tick should start
        next_tick_ts += TICK_LENGTH_MICROSECONDS;

        // sometimes TICK_LENGTH_MICROSECONDS isnt a natural number
        // so we have to account for that
        if (tick % REFRESH_RATE == 0)
        {
            next_tick_ts += TICK_REMINDER_MICROSECONDS;
        }

// debug stuff
#if DBGMSG_TICK_SYSTEM
        printf("tick no. %u\n", tick);

        uint32_t tick_start_ts;
        uint32_t tick_end_ts;

        // profiling stuff
        tick_start_ts = clock.get_new_ts();
#endif

        /// TODO: update CommunicationSystem

        // mainCommunicationSystem.update();

        // update all hardware controllers if they need to be updated
        for (int i = 0; i < HC_TABLE_LEN; ++i)
        {
            if (hctable[i] == nullptr)
                break;

            if (tick % (hctable[i])->get_update_frequency() == 0)
            {
                (hctable[i])->update();
            }
        }

        // update all rocket modules if they need to be updated
        for (int i = 0; i < RM_TABLE_LEN; ++i)
        {
            if (rmtable[i] == nullptr)
                break;

            if (tick % (rmtable[i])->get_update_frequency() == 0)
            {
                (rmtable[i])->update();
            }
        }

        // rocket's "mission code". all major operations that are
        // not related to data processing should be made transparent
        // by being put here.

#if DBGMSG_TICK_SYSTEM
        // profiling stuff
        tick_end_ts = clock.get_new_ts();

        printf("execution completed in %zu microseconds (%f%% of time used)\n", tick_end_ts - tick_start_ts, ((float)(tick_end_ts - tick_start_ts) / (float)TICK_LENGTH_MICROSECONDS) * 100);
        printf("waiting %zu microseconds to end of tick...\n", next_tick_ts - tick_end_ts);
#endif

        // exec completed, we need to wait
        while (current_tick_ts < next_tick_ts)
        {
            current_tick_ts = clock.get_new_ts();
        }
        ++tick;
    }

    return 0;
}
