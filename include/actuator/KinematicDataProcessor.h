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

class KinematicDataProcessor : public RocketModule, public Actuator
{
public:
    KinematicDataProcessor(const char* _name, int _update_frequency, Clock* _clock);
    void write_ornt(const Quaternion& q);
    void write_accl(const VectorInt16& v);
    void write_gyro(const VectorInt16& v);

    void get_gravity(VectorFloat* target, const Quaternion& q);
    void get_linear_accel(VectorInt16* v, VectorInt16* v_raw, VectorFloat* gravity);
    void get_linear_world_accel(VectorInt16* v, VectorInt16* v_linear, Quaternion* q);

    const int update() override;

private:
    // calculated
    Quaternion orientation_buffer[KDP_BUFFER_LENGTH];
    VectorFloat velocity_buffer[KDP_BUFFER_LENGTH];
    VectorFloat position_buffer[KDP_BUFFER_LENGTH];

    // sensed
    VectorInt16 accelerometer_buffer[KDP_BUFFER_LENGTH];
    VectorInt16 gyroscope_buffer[KDP_BUFFER_LENGTH];

    // ptrs
    uint8_t orientation_buffer_ptr = 0;
    uint8_t velocity_buffer_ptr = 0;
    uint8_t position_buffer_ptr = 0;

    uint8_t accelerometer_buffer_ptr = 0;
    uint8_t gyroscope_buffer_ptr = 0;

    Clock* clock_ref;
};

#endif