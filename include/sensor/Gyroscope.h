#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "control_interface/IGyroscopeControl.h"
#include "struct/GyroscopeDataPack.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class Gyroscope : public RocketModule,
                  public Sensor
{
public:
    Gyroscope(const char *_name,
              int _updateFrequency,
              TextDataSaver *_textDataSaver,
              Clock *_clock,
              IGyroscopeControl *_IGyroscopeController) : RocketModule(_name, _updateFrequency),
                                                          Sensor()
    {
        textDataSaver_ref = _textDataSaver;
        clock_ref = _clock;
        IGyroscopeController_ref = _IGyroscopeController;
    }

    int update()
    {
        return 0;
    }

private:
    GyroscopeDataPack latestValue;

    TextDataSaver *textDataSaver_ref;
    Clock *clock_ref;

    IGyroscopeControl *IGyroscopeController_ref;
};

#endif