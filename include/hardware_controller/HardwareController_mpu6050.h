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
#include "hardware/i2c.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"

#include "ext_lib/mpu6050/MPU6050_6Axis_MotionApps_V6_12.h"
#include "ext_lib/mpu6050/MPU6050.h"

class HardwareController_mpu6050 : public HardwareController,
    public IAccelerometerControl,
    public IGyroscopeControl
{
public:
    HardwareController_mpu6050(const char* _hardwareName, i2c_inst_t* _i2c_inst, uint _baudrate);
    const AccelerometerDataPack get_accelerometer_reading() override;
    const GyroscopeDataPack get_gyroscope_reading() override;
    const int update() override;

private:
    void init();
    void init_dmp();
    MPU6050 mpu;
    i2c_inst_t* i2c_inst;
    uint baudrate;

    uint8_t fifo_buffer[64];

    uint8_t interrupt_status;       // currently unused, we should be runnung getInterruptStatus to properly use this function of the mpu
    uint16_t fifo_packet_size;      // dmp packet size
    uint16_t fifo_count;            // dmp packet count in the fifo buffer

    bool dmp_ready;                 // use this to signal to update() that an interrupt happened
protected:
};

#endif