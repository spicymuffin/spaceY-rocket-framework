#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

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

class Accelerometer : public RocketModule,
    public Sensor
{
public:
    Accelerometer(const char* _name,
        int _update_frequency,
        TextDataSaver* _textDataSaver,
        Clock* _clock,
        IAccelerometerControl* _IAccelerometerController);
    const VectorInt16 getReading();
    const int update() override;

private:
    VectorInt16 latest_value;

    TextDataSaver* textDataSaver_ref;
    Clock* clock_ref;

    IAccelerometerControl* IAccelerometerControl_ref;
};

#endif