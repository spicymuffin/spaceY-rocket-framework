#include "base_class/HardwareLink.h"

#include "param.h"

#include "hardware_link/HardwareLink_mpu6050.h"

#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

HardwareLink_mpu6050::HardwareLink_mpu6050(char *_hardwareName)
    : HardwareLink(_hardwareName)
{
    /// TODO: initialize mpu6050
}

AccelerometerDataPack HardwareLink_mpu6050::getAccelerometerReading()
{
    AccelerometerDataPack test;
    test.acc_x = 0;
    test.acc_y = 0;
    test.acc_z = 0;
    return test;
}
