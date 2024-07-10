#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// dependencies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"

#include "control_interface/IServoControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// macros
#define PARACHUTE_CLOSED_SERVO_ANGLE 0
#define PARACHUTE_OPENED_SERVO_ANGLE 90

class ParachuteDeployer : public RocketModule,
    public Actuator
{
public:
    ParachuteDeployer(
        const char* _name,
        int _update_frequency,
        Accelerometer* _accelerometer,
        Gyroscope* _gyroscope,
        IServoControl* _IServoController);
    void deploy_parachute();
    const int update() override;

private:
    Accelerometer* accelerometer_ref;
    Gyroscope* gyroscope_ref;
    IServoControl* IServoController_ref;
};

#endif