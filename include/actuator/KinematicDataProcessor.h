#ifndef KINEMATICDATAPROCESSOR_H
#define KINEMATICDATAPROCESSOR_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// system
#include "system/Clock.h"
#include "system/RocketState.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/Altimeter.h"

// ext_lib
#include "ext_lib/math3d/math3d.h"

// util
#include "util/CircularBuffer.h"

class KinematicDataProcessor : public RocketModule, public Actuator
{
public:
    KinematicDataProcessor(const char* _name, int _update_frequency, Clock* _clock);

    void get_gravity(VectorFloat* v, Quaternion* q);
    void get_linear_accel(VectorInt16* v, VectorInt16* v_raw, VectorFloat* gravity);
    void get_world_linear_accel(VectorInt16* v, VectorInt16* v_linear, Quaternion* q);

    CircularBuffer<Quaternion>* get_orientation_buffer_ref();
    CircularBuffer<VectorFloat>* get_velocity_buffer_ref();
    CircularBuffer<VectorFloat>* get_position_buffer_ref();

    CircularBuffer<VectorInt16>* get_accelerometer_buffer_ref();
    CircularBuffer<VectorInt16>* get_gyroscope_buffer_ref();

    const int update() override;

private:
    // calculated (*)
    CircularBuffer<Quaternion> orientation_buffer;
    CircularBuffer<VectorFloat> velocity_buffer;
    CircularBuffer<VectorFloat> position_buffer;

    // sensed
    CircularBuffer<VectorInt16> accelerometer_buffer;
    CircularBuffer<VectorInt16> gyroscope_buffer;

    // temporary vars
    Quaternion ornt;
    VectorInt16 accl;
    VectorInt16 gyro;

    VectorFloat gravity;

    VectorInt16 linear_accel;

    VectorInt16 world_linear_accel;
    VectorInt16 prev_world_linear_accel;

    VectorInt16 world_velocity;
    VectorInt16 prev_world_velocity;

    VectorInt16 world_position;

    uint32_t prev_ts;
    uint32_t curr_ts;

    // // ptrs
    // uint8_t orientation_buffer_ptr = 0;
    // uint8_t velocity_buffer_ptr = 0;
    // uint8_t position_buffer_ptr = 0;

    // uint8_t accelerometer_buffer_ptr = 0;
    // uint8_t gyroscope_buffer_ptr = 0;

    Clock* clock_ref;
};

#endif