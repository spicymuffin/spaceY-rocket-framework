// implementing
#include "sensor/Accelerometer.h"

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

#include "control_interface/IAccelerometerControl.h"

Accelerometer::Accelerometer(const char* _name,
    int _update_frequency,
    TextDataSaver* _textDataSaver,
    Clock* _clock,
    IAccelerometerControl* _IAccelerometerController)

    :

    RocketModule(_name, _update_frequency),
    Sensor()
{
    textDataSaver_ref = _textDataSaver;
    clock_ref = _clock;
    IAccelerometerControl_ref = _IAccelerometerController;
}

const VectorInt16 Accelerometer::getReading()
{
    return IAccelerometerControl_ref->get_accelerometer_reading();
}

const int Accelerometer::update()
{
    return 0;
}