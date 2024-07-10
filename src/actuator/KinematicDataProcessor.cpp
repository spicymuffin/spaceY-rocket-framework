// implementing
#include "actuator/KinematicDataProcessor.h"

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// system
#include "system/Clock.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependcies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"

KinematicDataProcessor::KinematicDataProcessor(
    const char* _name,
    int _update_frequency,
    Clock* _clock)

    :

    RocketModule(_name, _update_frequency),
    Actuator()
{
    clock_ref = _clock;
}

void KinematicDataProcessor::write_ornt(const Quaternion& q)
{

}

void KinematicDataProcessor::write_accl(const VectorInt16& v)
{

}

void KinematicDataProcessor::write_gyro(const VectorInt16& v)
{

}

void KinematicDataProcessor::get_gravity(VectorFloat* target, const Quaternion& q)
{

}

void KinematicDataProcessor::get_linear_accel(VectorInt16* v, VectorInt16* v_raw, VectorFloat* gravity)
{

}

void KinematicDataProcessor::get_linear_world_accel(VectorInt16* v, VectorInt16* v_linear, Quaternion* q)
{

}

const int KinematicDataProcessor::update()
{
    // read all from gyro
    // read all from accel

}