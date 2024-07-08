#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "control_interface/IAccelerometerControl.h"
#include "struct/AccelerometerDataPack.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class Accelerometer : public RocketModule,
    public Sensor
{
public:
    Accelerometer(const char* _name,
        int _update_frequency,
        TextDataSaver* _textDataSaver,
        Clock* _clock,
        IAccelerometerControl* _IAccelerometerController) : RocketModule(_name, _update_frequency),
        Sensor()
    {
        textDataSaver_ref = _textDataSaver;
        clock_ref = _clock;
        IAccelerometerControl_ref = _IAccelerometerController;
    }

    const AccelerometerDataPack getReading()
    {
        return IAccelerometerControl_ref->get_accelerometer_reading();
    }

    int update()
    {
        return -1;
    }

private:
    AccelerometerDataPack latest_value;

    TextDataSaver* textDataSaver_ref;
    Clock* clock_ref;

    IAccelerometerControl* IAccelerometerControl_ref;
};

#endif