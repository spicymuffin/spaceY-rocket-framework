#ifndef HARDWARELINK_MPU6050_H
#define HARDWARELINK_MPU6050_H

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

class HardwareLink_mpu6050 : public HardwareLink
{
public:
    HardwareLink_mpu6050(const char *_hardwareName);
    const AccelerometerDataPack getAccelerometerReading();
    const AngularAccelerometerDataPack getAngularAccelerometerReading();
    const GyroscopeDataPack getGyroscopeReading();

private:
protected:
};

#endif