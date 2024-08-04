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

// util
#include "util/CircularBuffer.h"

class HardwareController_mpu6050 : public HardwareController,
    public IAccelerometerControl,
    public IGyroscopeControl
{
public:
    HardwareController_mpu6050(
        const char* _hardware_name,
        int _update_frequency,
        i2c_inst_t* _i2c_inst,
        uint _baudrate,
        // arrays of pointers btw
        CircularBuffer<VectorInt16>* _accelerometer_data_receivers[],
        CircularBuffer<VectorInt16>* _gyroscope_data_receivers[],
        CircularBuffer<Quaternion>* _orientation_data_receivers[],
        uint8_t _norientation_data_receivers,
        uint8_t _naccelerometer_data_receivers,
        uint8_t _ngyroscope_data_receivers);

    const VectorInt16 get_accelerometer_reading() override;
    const VectorInt16 get_gyroscope_reading() override;
    const int update() override;

private:
    void init();
    void init_dmp();

    // pointers to arrays of pointers
    CircularBuffer<Quaternion>** orientation_data_receivers_ref;
    CircularBuffer<VectorInt16>** accelerometer_data_receivers_ref;
    CircularBuffer<VectorInt16>** gyroscope_data_receivers_ref;

    // length of arrays
    uint8_t norientation_data_receivers;
    uint8_t naccelerometer_data_receivers;
    uint8_t ngyroscope_data_receivers;

    // temporary variables
    Quaternion  ornt;
    VectorInt16 accl;
    VectorInt16 gyro;

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