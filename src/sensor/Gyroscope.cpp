// implementing
#include "sensor/Gyroscope.h"

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

#include "control_interface/IGyroscopeControl.h"

Gyroscope::Gyroscope(const char* _name,
    int _update_frequency,
    TextDataSaver* _textDataSaver,
    Clock* _clock,
    IGyroscopeControl* _IGyroscopeController)

    :

    RocketModule(_name, _update_frequency),
    Sensor()
{
    textDataSaver_ref = _textDataSaver;
    clock_ref = _clock;
    IGyroscopeController_ref = _IGyroscopeController;
}

const VectorInt16 Gyroscope::getReading()
{
    return IGyroscopeController_ref->get_gyroscope_reading();
}

const int Gyroscope::update()
{
    return 0;
}

