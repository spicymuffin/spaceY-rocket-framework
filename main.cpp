/**
 * @file main.cpp
 * @author luigi (luigicussigh59@gmail.com)
 * @brief spaceY's rocket control software
 * @version 1.1
 * @date 2023-11-20
 *
 * @copyright lol somepne should pay me for this
 *
 *
 * use cmake to build this crap
 */

// param
#include "param.h"

// base classes
#include "base_class/RocketModule.h"

// systems
#include "system/FlightLogger.h"
#include "system/Clock.h"
#include "system/CommunicationSystem.h"

// HardwareLinks
#include "hardware_link/HardwareLink_mpu6050.h"
#include "hardware_link/HardwareLink_fuelcelligniter.h"
#include "hardware_link/HardwareLink_onboardled.h"
#include "hardware_link/HardwareLink_servotype0.h"
#include "hardware_link/HardwareLink_usb.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// constants
// this is all unusuble unless someone makes the USB thing work ;-;
// const string FLIGHT_LOGS_DIRECTORY = "/data/flight logs";
// const string IMU_LOGS_DIRECTORY = "/data/IMU logs";

// const string COMMUNICATION_PROTOCOL_PATH = "/communication_protocols/mainprotocol.json";

const uint32_t REFRESH_RATE = 10; // in Hz
const uint32_t MICROSECONDS_PER_SECOND = 1000000;

// calculated at runtime
uint32_t TICK_LENGTH_MICROSECONDS = -1;
uint32_t TICK_REMINDER_MICROSECONDS = -1;

// tick of rocket
unsigned int tick = 0;

// current tick's start's timestamp

uint32_t currentTickTimestamp = 0; // TODO: change to longs
// next tick's start's timestamp
uint32_t nextTickTimestamp = 0;

// if set to true the main loop will run endlessly
bool ENDLESS = false;

// if [ENDLESS] is set to false main loop will run for [TEST_DURATION] seconds
uint32_t TEST_DURATION = 10;

RocketModule *modules[RM_TABLE_LEN];

int main(int argc, char *argv[])
{
    printf("intitializing...\n");

    stdio_init_all();

    for (int i = 0; i < RM_TABLE_LEN; i++)
    {
        modules[i] = nullptr;
    }

    /// TODO: move to macros?
    // calculate lengths
    TICK_LENGTH_MICROSECONDS = MICROSECONDS_PER_SECOND / REFRESH_RATE;
    TICK_REMINDER_MICROSECONDS = MICROSECONDS_PER_SECOND % REFRESH_RATE;

#pragma region initialize rocket systems

    // init clock
    Clock mainClock = Clock();
    printf("system clock initialized.\n");
    printf("TICK_LENGTH_MICROSECONDS: %zu\n", TICK_LENGTH_MICROSECONDS);
    printf("TICK_REMINDER_MICROSECONDS: %zu\n", TICK_REMINDER_MICROSECONDS);

    // initialize flight log
    // FlightLogger flightLog = FlightLogger("main flight log", cur_dir + FLIGHT_LOGS_DIRECTORY, "flight_log");
    // printf("%s initialized.\n", flightLog.getName());

#pragma endregion

#pragma region initialize hardware

    /// TODO: initialize hardware

#pragma endregion

#pragma region intialize communication systems

    // vector<RocketModule *> mainCommuniationSystem_Modules = {};
    //  init main Communication System
    // CommunicationSystem mainCommunicationSystem = CommunicationSystem("main communication system", 10, mainCommuniationSystem_Modules, cur_dir + COMMUNICATION_PROTOCOL_PATH);

#pragma endregion

    currentTickTimestamp = mainClock.getNewTimestamp();
    nextTickTimestamp = currentTickTimestamp;

    while (ENDLESS ? true : tick <= REFRESH_RATE * TEST_DURATION - 1)
    {
        // record this tick's start's timestamp
        currentTickTimestamp = mainClock.getNewTimestamp();

        // calculate when next tick should start
        nextTickTimestamp += TICK_LENGTH_MICROSECONDS;

        // sometimes TICK_LENGTH_MICROSECONDS isnt a natural number
        // so we have to account for that
        if (tick % REFRESH_RATE == 0)
        {
            nextTickTimestamp += TICK_REMINDER_MICROSECONDS;
        }

        // debug stuff
        printf("tick no. %u\n", tick);

        uint32_t tickStartTimestamp;
        uint32_t tickEndTimestamp;

        // profiling stuff
        tickStartTimestamp = mainClock.getNewTimestamp();

        /// TODO: update CommunicationSystem

        // mainCommunicationSystem.update();

        // update all rocket modules if they need to be updated
        for (int i = 0; i < RM_TABLE_LEN; ++i)
        {
            if (modules[i] != nullptr && tick % (modules[i])->getUpdateFrequency() == 0)
            {
                (modules[i])->update();
            }
        }

        // profiling stuff
        tickEndTimestamp = mainClock.getNewTimestamp();

        printf("execution completed in %zu microseconds (%f%% of time used)\n", tickEndTimestamp - tickStartTimestamp, ((float)(tickEndTimestamp - tickStartTimestamp) / (float)TICK_LENGTH_MICROSECONDS) * 100);
        printf("waiting %zu microseconds to end of tick...\n", nextTickTimestamp - tickEndTimestamp);

        // exec completed, we need to wait
        while (currentTickTimestamp < nextTickTimestamp)
        {
            currentTickTimestamp = mainClock.getNewTimestamp();
        }
        ++tick;
    }

    printf("execution complete...\n");
    return 0;
}
