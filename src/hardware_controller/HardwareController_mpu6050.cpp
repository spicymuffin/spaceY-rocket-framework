// implementing
#include "hardware_controller/HardwareController_mpu6050.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependcies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

HardwareController_mpu6050::HardwareController_mpu6050(const char *_hardwareName)
    : HardwareController(_hardwareName)
{
    strcpy(hardwareName, _hardwareName);
}

const AccelerometerDataPack HardwareController_mpu6050::getAccelerometerReading()
{
    AccelerometerDataPack test;
    test.x = 0;
    test.y = 0;
    test.z = 0;
    return test;
}
