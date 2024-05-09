#ifndef ANGULARACCELEROMETER_H
#define ANGULARACCELEROMETER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"

// dependencies
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

#include "control_interface/IAngularAccelerometerControl.h"
#include "struct/AngularAccelerometerDataPack.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class AngularAccelerometer : public RocketModule,
                             public Sensor
{
public:
    AngularAccelerometer(const char *_name,
                         int _updateFrequency,
                         TextDataSaver *_textDataSaver,
                         Clock *_clock,
                         IAngularAccelerometerControl *_IAngularAccelerometerController) : RocketModule(_name, _updateFrequency),
                                                                                           Sensor()
    {
        IAngularAccelerometerController_ref = _IAngularAccelerometerController;
    }

    int update()
    {
        return -1;
    }

    const AngularAccelerometerDataPack getAngularAccelerometerReading()
    {
        return IAngularAccelerometerController_ref->getAngularAccelerometerReading();
    }

private:
    AngularAccelerometerDataPack latestValue;

    TextDataSaver *textDataSaver;
    Clock *clock;

    IAngularAccelerometerControl *IAngularAccelerometerController_ref;
};

#endif