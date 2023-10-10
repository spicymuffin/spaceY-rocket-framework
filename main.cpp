#include "./headers/RocketModule.h"
#include "./headers/FlightLogger.h"
#include "./headers/IMU.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "initializing rocket.." << endl;
    std::string cur_dir(argv[0]);

    int pos = cur_dir.find_last_of("/\\");
    cout << cur_dir << endl;
    // init classes
    FlightLogger mainLogger = FlightLogger("main log", 1024);
    mainLogger.writeData();

    IMU mainIMU = IMU("mainIMU", 100);
    cout << mainIMU.getName() << endl;
    return 0;
}
