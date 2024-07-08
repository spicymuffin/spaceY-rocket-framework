#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "control_interface/IAltimeterControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class Altimeter : public RocketModule,
    public Sensor
{
public:
    Altimeter(const char* _name,
        int _updateFrequency,
        TextDataSaver* _textDataSaver,
        Clock* _clock,
        IAltimeterControl* _IAltimeterController) : RocketModule(_name, _updateFrequency), Sensor()
    {
        textDataSaver_ref = _textDataSaver;
        clock_ref = _clock;
        IAltimeterController_ref = _IAltimeterController;
    }

    int update()
    {
        return 0;
    }

private:
    float latest_value;

    TextDataSaver* textDataSaver_ref;
    Clock* clock_ref;

    IAltimeterControl* IAltimeterController_ref;
};

#endif