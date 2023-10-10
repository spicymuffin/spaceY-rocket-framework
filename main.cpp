#include "./headers/RocketModule.h"
#include "./headers/FlightLogger.h"
#include "./headers/IMU.h"

#include <iostream>
#include <string>

using namespace std;

const string FLIGHT_LOGS_DIRECTORY = "\\logs\\flight logs";
const string IMU_LOGS_DIRECTORY = "\\logs\\IMU logs";

int main(int argc, char *argv[])
{
    cout << "initializing rocket.." << endl;
    std::string cur_dir(argv[0]);

    int pos = cur_dir.find_last_of("/\\");

    int i = cur_dir.length() - 1;
    while (cur_dir[i] != '\\')
    {
        cur_dir.pop_back();
        --i;
    }
    cur_dir.pop_back();

    cout << cur_dir << endl;

    // init classes

    // initialize flight log
    FlightLogger flightLog = FlightLogger("main log");
    flightLog.dumpTickBuffer();

    IMU mainIMU = IMU("mainIMU", 100);
    cout << mainIMU.getName() << endl;

    TextDataSaver IMULog = TextDataSaver("IMU log", -1, cur_dir + IMU_LOGS_DIRECTORY);

    return 0;
}
