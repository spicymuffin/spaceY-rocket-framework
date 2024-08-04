// implementing
#include "actuator/KinematicDataProcessor.h"

#include "param.h"
#include "debug_param.h"

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

// util
#include "util/CircularBuffer.h"

KinematicDataProcessor::KinematicDataProcessor(
    const char* _name,
    int _update_frequency,
    Clock* _clock)

    :

    RocketModule(_name, _update_frequency),
    Actuator()
{
    #if DBGMSG_KDP
    printf("[STATUS]:[KDP] statrting initialization sequence\n");
    #endif

    clock_ref = _clock;
    prev_ts = clock_ref->get_new_ts();

    #if DBGMSG_KDP
    printf("[  OK  ]:[KDP] variables initialization complete\n");
    #endif

    orientation_buffer = CircularBuffer<Quaternion>();
    velocity_buffer = CircularBuffer<VectorFloat>();
    position_buffer = CircularBuffer<VectorFloat>();

    accelerometer_buffer = CircularBuffer<VectorInt16>();
    gyroscope_buffer = CircularBuffer<VectorInt16>();

    #if DBGMSG_KDP
    printf("[  OK  ]:[KDP] circular buffers initialization complete\n");
    #endif
}

CircularBuffer<Quaternion>* KinematicDataProcessor::get_orientation_buffer_ref()
{
    return &orientation_buffer;
}

CircularBuffer<VectorFloat>* KinematicDataProcessor::get_velocity_buffer_ref()
{
    return &velocity_buffer;
}

CircularBuffer<VectorFloat>* KinematicDataProcessor::get_position_buffer_ref()
{
    return &position_buffer;
}

CircularBuffer<VectorInt16>* KinematicDataProcessor::get_accelerometer_buffer_ref()
{
    return &accelerometer_buffer;
}

CircularBuffer<VectorInt16>* KinematicDataProcessor::get_gyroscope_buffer_ref()
{
    return &gyroscope_buffer;
}

void KinematicDataProcessor::get_gravity(VectorFloat* v, Quaternion* q)
{
    v->x = 2 * (q->x * q->z - q->w * q->y);
    v->y = 2 * (q->w * q->x + q->y * q->z);
    v->z = q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z;
}

void KinematicDataProcessor::get_linear_accel(VectorInt16* v, VectorInt16* v_raw, VectorFloat* gravity)
{
    // get rid of the gravity component (+1g = +8192 in standard DMP FIFO packet, sensitivity is 2g)
    v->x = v_raw->x - gravity->x * 8192 * 2;
    v->y = v_raw->y - gravity->y * 8192 * 2;
    v->z = v_raw->z - gravity->z * 8192 * 2;
    // printf("graivity: %f, %f, %f\n", gravity->x, gravity->y, gravity->z);
    // printf("v_raw: %d, %d, %d\n", v_raw->x, v_raw->y, v_raw->z);
    // printf("v: %d, %d, %d\n", v->x, v->y, v->z);
}

void KinematicDataProcessor::get_world_linear_accel(VectorInt16* v, VectorInt16* v_linear, Quaternion* q)
{
    // rotate measured 3D acceleration vector into original state
    // frame of reference based on orientation quaternion
    memcpy(v, v_linear, sizeof(VectorInt16));
    v->rotate(q);
}

const int KinematicDataProcessor::update()
{
    #if DBGMSG_KDP
    printf("[STATUS]:[KDP] updating\n");
    #endif

    // if orientation buffer got new, everything should've gotten new
    // (if not the data supply mechanism is bad)
    if (!(orientation_buffer.get_new_cnt() > 0)) { return 1; }

    // read data from buffer into ornt local var
    orientation_buffer.buffer_read(&ornt);

    // read data from buffer into accl local var
    accelerometer_buffer.buffer_read(&accl);

    // get gravity vector
    get_gravity(&gravity, &ornt);

    float lin_ax, lin_ay, lin_az;

    lin_ax = (float)accl.x / 16384.0 - gravity.x;
    lin_ay = (float)accl.y / 16384.0 - gravity.y;
    lin_az = (float)accl.z / 16384.0 - gravity.z;

    printf("acc: %f, %f, %f\n", lin_ax, lin_ay, lin_az);

    // get rid of gravity component in acceleration
    get_linear_accel(&linear_accel, &accl, &gravity);

    // get world frame acceleration
    get_world_linear_accel(&world_linear_accel, &linear_accel, &ornt);

    curr_ts = clock_ref->get_new_ts();

    uint32_t dt = curr_ts - prev_ts;

    world_velocity.x = prev_world_velocity.x + 0.5 * (prev_world_linear_accel.x + world_linear_accel.x) * dt;
    world_velocity.y = prev_world_velocity.y + 0.5 * (prev_world_linear_accel.y + world_linear_accel.y) * dt;
    world_velocity.z = prev_world_velocity.z + 0.5 * (prev_world_linear_accel.z + world_linear_accel.z) * dt;

    world_position.x = world_position.x + 0.5 * (prev_world_velocity.x + world_velocity.x) * dt;
    world_position.y = world_position.y + 0.5 * (prev_world_velocity.y + world_velocity.y) * dt;
    world_position.z = world_position.z + 0.5 * (prev_world_velocity.z + world_velocity.z) * dt;

    prev_world_linear_accel = world_linear_accel;
    prev_world_velocity = world_velocity;
    prev_ts = curr_ts;

    // printf("current accel: %d, %d, %d\n", world_linear_accel.x, world_linear_accel.y, world_linear_accel.z);
    // printf("current position: %d, %d, %d\n", world_position.x, world_position.y, world_position.z);

    return 0;
}