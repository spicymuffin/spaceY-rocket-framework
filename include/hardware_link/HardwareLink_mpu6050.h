#ifndef HARDWARELINK_MPU6050_H
#define HARDWARELINK_MPU6050_H

#include "base_class/HardwareLink.h"

#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

class HardwareLink_mpu6050 : public HardwareLink
{
public:
    HardwareLink_mpu6050(char *_hardwaremodelName);
    AccelerometerDataPack getAccelerometerReading();
    AngularAccelerometerDataPack getAngularAccelerometerReading();
    GyroscopeDataPack getGyroscopeReading();

private:
protected:
};

#endif