#include <iostream>
#include "RocketModule.h"
#include "FlightLogger.h"
#include "IMU.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "initializing rocket.." << endl;
    // init classes
    FlightLogger mainLogger = FlightLogger("main log", 1024);
    mainLogger.writeData();

    IMU mainIMU = IMU("mainIMU", 100);
    cout << mainIMU.getName() << endl;
    return 0;
}
