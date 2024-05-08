// implementing
#include "hardware_link/HardwareLink_mpu6050.h"

#include "param.h"

// base_class
#include "base_class/HardwareLink.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// depends on
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

HardwareLink_mpu6050::HardwareLink_mpu6050(const char *_hardwareName)
    : HardwareLink(_hardwareName)
{
    strcpy(hardwareName, _hardwareName);
}

const AccelerometerDataPack HardwareLink_mpu6050::getAccelerometerReading()
{
    AccelerometerDataPack test;
    test.acc_x = 0;
    test.acc_y = 0;
    test.acc_z = 0;
    return test;
}
