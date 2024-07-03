#ifndef HARDWARECONTROLLER_MPU6050_H
#define HARDWARECONTROLLER_MPU6050_H

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// implements
#include "control_interface/IAccelerometerControl.h"
#include "control_interface/IGyroscopeControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "ext_lib/mpu6050/MPU6050.h"

class HardwareController_mpu6050 : public HardwareController,
                                   public IAccelerometerControl,
                                   public IGyroscopeControl
{
public:
    HardwareController_mpu6050(const char *_hardwareName);
    const AccelerometerDataPack getAccelerometerReading() override;
    const GyroscopeDataPack getGyroscopeReading() override;

private:
    MPU6050 mpu;
protected:
};

#endif