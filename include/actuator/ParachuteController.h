#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

// dependencies

#include "param.h"

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

#include "sensor/Accelerometer.h"
#include "sensor/AngularAccelerometer.h"
#include "sensor/Gyroscope.h"

class ParachuteController : public RocketModule, public Actuator
{

    /// TODO: add open sensitivity parameter(s)
public:
    /// TODO: parachute controller initialization has references to acc, angacc, gyro
    ParachuteController(char *_name,
                        int _updateFrequency,
                        Accelerometer *_accelerometer,
                        AngularAccelerometer *_angularAccelerometer,
                        Gyroscope *_gyroscope);

    void deployParachute();
    int update() override;

private:
    Accelerometer *accelerometer_ref;
    AngularAccelerometer *angularAccelerometer_ref;
    Gyroscope *gyroscope_ref;
};

#endif