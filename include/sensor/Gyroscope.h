#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "ext_lib/math3d/math3d.h"

#include "control_interface/IGyroscopeControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class Gyroscope : public RocketModule,
    public Sensor
{
public:
    Gyroscope(const char* _name,
        int _updateFrequency,
        TextDataSaver* _textDataSaver,
        Clock* _clock,
        IGyroscopeControl* _IGyroscopeController);
    const VectorInt16 getReading();
    const int update() override;

private:
    VectorInt16 latest_value;

    TextDataSaver* textDataSaver_ref;
    Clock* clock_ref;

    IGyroscopeControl* IGyroscopeController_ref;
};

#endif