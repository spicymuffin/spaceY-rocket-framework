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

void init() {
    
}

void init_dmp() {
    
}

HardwareController_mpu6050::HardwareController_mpu6050(const char* _hardwareName)
    : HardwareController(_hardwareName)
{
}

const AccelerometerDataPack HardwareController_mpu6050::getAccelerometerReading()
{
    printf("-----------------> accelerometer reading\n");
    return {};
}

const GyroscopeDataPack HardwareController_mpu6050::getGyroscopeReading()
{
    printf("-----------------> gyroscope reading\n");
    return {};
}