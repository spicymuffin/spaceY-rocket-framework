#include "HardwareLink.h"
#include "HardwareLink_bosch.h"

#include "Accelerometer.h"
#include "Thermometer.h"
#include "Gyroscope.h"
#include "AngularAccelerometer.h"
#include "Altimeter.h"

using namespace std;

#include <string>

HardwareLink_bosch::HardwareLink_bosch(string _hardwareName) : HardwareLink(_hardwareName)
{
}

AccelerometerDataPack HardwareLink_bosch::getAccelerometerReading()
{
    AccelerometerDataPack test;
    test.acc_x = 0;
    test.acc_y = 0;
    test.acc_z = 0;
    return test;
}
