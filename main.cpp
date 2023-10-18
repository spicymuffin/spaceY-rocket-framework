#include "./headers/RocketModule.h"
#include "./headers/FlightLogger.h"
#include "./headers/IMU.h"
#include "./headers/Clock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string FLIGHT_LOGS_DIRECTORY = "/logs/flight logs";
const string IMU_LOGS_DIRECTORY = "/logs/IMU logs";

const int REFRESH_RATE = 2048 * 8; // Hz
const int MICROSECONDS_PER_SECOND = 1000000;

int TICK_LENGTH_MICROSECONDS = -1;
int TICK_REMINDER_MICROSECONDS = -1;

unsigned int tick = 0;
long long currentTickTimestamp = 0; // TODO: change to longs
long long nextTickTimestamp = 0;

bool ENDLESS = false;
int TEST_DURATION = 10;

vector<RocketModule *> modules;

int main(int argc, char *argv[])
{
    clock_t t;
    t = clock();
    cout << "initializing rocket.." << endl;

    cout << "doing pre calculations..." << endl;

    TICK_LENGTH_MICROSECONDS = MICROSECONDS_PER_SECOND / REFRESH_RATE;
    TICK_REMINDER_MICROSECONDS = MICROSECONDS_PER_SECOND % REFRESH_RATE;

#pragma region figure out current directory

    std::string cur_dir(argv[0]);
    int pos = cur_dir.find_last_of("/\\");
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

    mainClock.update();
    nextTickTimestamp = currentTickTimestamp;

    while (ENDLESS ? true : tick <= REFRESH_RATE * TEST_DURATION - 1)
    {
        mainClock.update();
        nextTickTimestamp += TICK_LENGTH_MICROSECONDS;

        if (tick % REFRESH_RATE == 0) // mega precision, might make things slower for a very little amount of precision lol
        {
            nextTickTimestamp += TICK_REMINDER_MICROSECONDS;
        }

        cout << "tick no. " << tick << endl;

        long long tickStartTimestamp;
        long long tickEndTimestamp;

        // profiling stuff
        tickStartTimestamp = mainClock.getTimestamp();

        for (int i = 0; i < static_cast<int>(modules.size()); ++i)
        {
            modules[i]->update();
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
    t = clock() - t;
    cout << tick << " ticks completed in " << t / 1000000.0 << " seconds" << endl;

    return 0;
}
