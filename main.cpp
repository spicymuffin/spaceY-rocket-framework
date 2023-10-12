#include "./headers/RocketModule.h"
#include "./headers/FlightLogger.h"
#include "./headers/IMU.h"
#include "./headers/Clock.h"

#include <iostream>
#include <string>

using namespace std;

const string FLIGHT_LOGS_DIRECTORY = "\\logs\\flight logs";
const string IMU_LOGS_DIRECTORY = "\\logs\\IMU logs";

const int REFRESH_RATE = 64; // Hz
const int MICROSECONDS_PER_SECOND = 1000000;
int TICK_LENGTH_MICROSECONDS = -1;

unsigned int tick = 0;
long long currentTimestamp = 0; // TODO: change to longs
long long nextTickTimestamp = 0;

bool ENDLESS = false;
int TEST_DURATION = 60 * 60;

int main(int argc, char *argv[])
{
    clock_t t;
    t = clock();
    cout << "initializing rocket.." << endl;

    cout << "doing pre calculations..." << endl;

    TICK_LENGTH_MICROSECONDS = MICROSECONDS_PER_SECOND / REFRESH_RATE;

#pragma region figure out current directory

    std::string cur_dir(argv[0]);
    int pos = cur_dir.find_last_of("/\\");
    int i = cur_dir.length() - 1;
    while (cur_dir[i] != '\\')
    {
        cur_dir.pop_back();
        --i;
    }
    cur_dir.pop_back();
    cout << "working directory: " << cur_dir << endl;

#pragma endregion

#pragma region initialize rocket systems

    // init clock
    Clock mainClock(&currentTimestamp);
    cout << "system clock initialized." << endl;

    // initialize flight log
    FlightLogger flightLog = FlightLogger("main flight log", cur_dir + FLIGHT_LOGS_DIRECTORY, "flight_log");
    cout << flightLog.getName() << " initialized." << endl;

#pragma endregion

#pragma region initialize rocket components

    // init IMU data saver
    TextDataSaver IMUDataSaver = TextDataSaver("main IMU data saver", -1, cur_dir + IMU_LOGS_DIRECTORY, "mainIMU");
    cout << IMUDataSaver.getName() << " initialized." << endl;

    // init IMU
    IMU mainIMU = IMU("main IMU", 1, &IMUDataSaver);
    cout << mainIMU.getName() << " initialized." << endl;

#pragma endregion

    while (ENDLESS ? true : tick <= REFRESH_RATE * TEST_DURATION)
    {
        mainClock.update();
        nextTickTimestamp = currentTimestamp + TICK_LENGTH_MICROSECONDS;
        cout << "tick no. " << tick << endl;

        long long tickStartTimestamp;
        long long tickEndTimestamp;

        // profiling stuff
        tickStartTimestamp = mainClock.getTimestamp();

        mainIMU.update();

        // profiling stuff
        tickEndTimestamp = mainClock.getTimestamp();

        cout << "execution completed in " << tickEndTimestamp - tickStartTimestamp << " microseconds (" << (float)(tickEndTimestamp - tickStartTimestamp) / (float)TICK_LENGTH_MICROSECONDS * 100 << "% of time used)" << endl;
        cout << "waiting " << nextTickTimestamp - tickEndTimestamp << " microseconds to end of tick..." << endl;

        // exec completed, we need to wait
        while (currentTimestamp < nextTickTimestamp)
        {
            mainClock.update();
        }
        ++tick;
    }
    t = clock() - t;
    cout << tick << " ticks completed in " << t << " milliseconds" << endl;

    return 0;
}
