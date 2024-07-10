// implementing
#include "sensor/Altimeter.h"

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "ext_lib/math3d/math3d.h"

#include "control_interface/IAltimeterControl.h"

Altimeter::Altimeter(const char* _name,
    int _update_frequency,
    TextDataSaver* _textDataSaver,
    Clock* _clock,
    IAltimeterControl* _IAltimeterController)

    :

    RocketModule(_name, _update_frequency),
    Sensor()
{
    textDataSaver_ref = _textDataSaver;
    clock_ref = _clock;
    IAltimeterController_ref = _IAltimeterController;
}

const int Altimeter::update()
{
    return 0;
}