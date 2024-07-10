// implementing
#include "actuator/ParachuteDeployer.h"

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

ParachuteDeployer::ParachuteDeployer(
    const char* _name,
    int _update_frequency,
    Accelerometer* _accelerometer,
    Gyroscope* _gyroscope,
    IServoControl* _IServoController)

    :

    RocketModule(_name, _update_frequency),
    Actuator()
{
    IServoController_ref = _IServoController;
}

void ParachuteDeployer::deploy_parachute()
{
    IServoController_ref->set_angle(PARACHUTE_OPENED_SERVO_ANGLE);
}

const int update()
{
    return 0;
}