/**
 * @file main.cpp
 * @author luigi (luigicussigh59@gmail.com)
 * @brief spaceY's rocket control software
 * @version 1.1
 * @date 2023-11-20
 *
 * @copyright lol
 *
 *
 * use sh build.sh to compile this file
 */

#include "./classes/RocketModule.h"
#include "./classes/FlightLogger.h"
#include "./classes/IMU.h"
#include "./classes/Clock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string FLIGHT_LOGS_DIRECTORY = "/logs/flight logs";
const string IMU_LOGS_DIRECTORY = "/logs/IMU logs";

const int REFRESH_RATE = 64; // in Hz
const int MICROSECONDS_PER_SECOND = 1000000;

// calculated at runtime
int TICK_LENGTH_MICROSECONDS = -1;
int TICK_REMINDER_MICROSECONDS = -1;

// tick of rocket
unsigned int tick = 0;

// current tick's start's timestamp
long long currentTickTimestamp = 0; // TODO: change to longs
// next tick's start's timestamp
long long nextTickTimestamp = 0;

// if set to true the main loop will run endlessly
bool ENDLESS = false;

// if [ENDLESS] is set to false main loop will run for [TEST_DURATION] seconds
unsigned int TEST_DURATION = 4;

vector<RocketModule *> modules;

int main(int argc, char *argv[])
{
    // clock object used for debugging puroses
    clock_t t;
    t = clock();

    // debug msgs
    cout << "initializing rocket.." << endl;

    cout << "doing pre calculations..." << endl;

    // calculate lengths
    TICK_LENGTH_MICROSECONDS = MICROSECONDS_PER_SECOND / REFRESH_RATE;
    TICK_REMINDER_MICROSECONDS = MICROSECONDS_PER_SECOND % REFRESH_RATE;

#pragma region figure out current directory

    // figure out working directory (linux)
    std::string cur_dir(argv[0]);
    // int pos = cur_dir.find_last_of("/\\");
    int i = cur_dir.length() - 1;
    while (cur_dir[i] != '/')
    {
        cur_dir.pop_back();
        --i;
    }
    cur_dir.pop_back();
    cout << "working directory: " << cur_dir << endl;

#pragma endregion

#pragma region initialize rocket systems

    // init clock
    Clock mainClock(&currentTickTimestamp);
    cout << "system clock initialized." << endl;

    // initialize flight log
    FlightLogger flightLog = FlightLogger("main flight log", cur_dir + FLIGHT_LOGS_DIRECTORY, "flight_log");
    cout << flightLog.getName() << " initialized." << endl;

#pragma endregion

#pragma region initialize rocket modules

    // init IMU data saver
    TextDataSaver IMUDataSaver = TextDataSaver("main IMU data saver", -1, cur_dir + IMU_LOGS_DIRECTORY, "mainIMU");
    cout << IMUDataSaver.getName() << " initialized." << endl;
    modules.push_back(&IMUDataSaver);

    // init IMU
    IMU mainIMU = IMU("main IMU", 1, &IMUDataSaver, &mainClock);
    cout << mainIMU.getName() << " initialized." << endl;
    modules.push_back(&mainIMU);

#pragma endregion

    // updating main clock sets [currentTickTimestamp] to current timestamp.
    mainClock.update();
    // init this variable
    nextTickTimestamp = currentTickTimestamp;

    while (ENDLESS ? true : tick <= REFRESH_RATE * TEST_DURATION - 1)
    {
        // record this tick's start's timestamp
        mainClock.update();
        // calculate when next tick should start
        nextTickTimestamp += TICK_LENGTH_MICROSECONDS;

        if (tick % REFRESH_RATE == 0)
        {
            nextTickTimestamp += TICK_REMINDER_MICROSECONDS;
        }

        // debug stuff
        cout << "tick no. " << tick << endl;

        long long tickStartTimestamp;
        long long tickEndTimestamp;

        // profiling stuff
        tickStartTimestamp = mainClock.getTimestamp();

        // update all rocket modules f they need to be updated
        for (int i = 0; i < static_cast<int>(modules.size()); ++i)
        {
            if (tick % modules[i]->getUpdateFrequency() == 0){
                modules[i]->update();
            }
        }

        // profiling stuff
        tickEndTimestamp = mainClock.getTimestamp();

        cout << "execution completed in " << tickEndTimestamp - tickStartTimestamp << " microseconds (" << (float)(tickEndTimestamp - tickStartTimestamp) / (float)TICK_LENGTH_MICROSECONDS * 100 << "% of time used)" << endl;
        cout << "waiting " << nextTickTimestamp - tickEndTimestamp << " microseconds to end of tick..." << endl;

        // exec completed, we need to wait
        while (currentTickTimestamp < nextTickTimestamp)
        {
            mainClock.update();
        }
        ++tick;
    }

    // measure execution time
    t = clock() - t;
    cout << tick << " ticks completed in " << t / 1000000.0 << " seconds" << endl;

    return 0;
}
