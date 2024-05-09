#ifndef HARDWARECONTROLLER_MPU6050_H
#define HARDWARECONTROLLER_MPU6050_H

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// implements
#include "control_interface/IAccelerometerControl.h"
#include "control_interface/IAngularAccelerometerControl.h"
#include "control_interface/IGyroscopeControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

class HardwareController_mpu6050 : public HardwareController,
                                   public IAccelerometerControl,
                                   public IAngularAccelerometerControl,
                                   public IGyroscopeControl
{
public:
    HardwareController_mpu6050(const char *_hardwareName);
    const AccelerometerDataPack getAccelerometerReading();
    const AngularAccelerometerDataPack getAngularAccelerometerReading();
    const GyroscopeDataPack getGyroscopeReading();

private:
protected:
};

#endif