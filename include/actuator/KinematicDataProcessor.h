#ifndef KINEMATICDATAPROCESSOR_H
#define KINEMATICDATAPROCESSOR_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// system
#include "system/Clock.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/Altimeter.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// ext_lib
#include "ext_lib/math3d/math3d.h"

class KinematicDataProcessor : public RocketModule, public Actuator
{
public:
    KinematicDataProcessor(const char* _name, int _updateFrequency, Clock* _clock);
    void write_ornt(const Quaternion& q);
    void write_accl(const VectorInt16& v);
    void write_gyro(const VectorInt16& v);

    void get_gravity(VectorFloat* target, const Quaternion& q);

private:
    Quaternion orientation_buffer[KDP_BUFFER_LENGTH];
    VectorInt16 accelerometer_buffer[KDP_BUFFER_LENGTH];
    VectorInt16 gyroscope_buffer[KDP_BUFFER_LENGTH];

    uint8_t orientation_buffer_ptr = 0;
    uint8_t accelerometer_buffer_ptr = 0;
    uint8_t gyroscope_buffer_ptr = 0;

    Clock* clock_ref;
};

#endif