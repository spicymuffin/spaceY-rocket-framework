#ifndef ANGULARACCELEROMETER_H
#define ANGULARACCELEROMETER_H

#include "param.h"

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

struct AngularAccelerometerDataPack
{
    double acc_x;
    double acc_y;
    double acc_z;
};

class AngularAccelerometer : public RocketModule, public Sensor
{
public:
    AngularAccelerometer(const char *_name,
                         int _updateFrequency,
                         TextDataSaver *_textDataSaver,
                         Clock *_clock,
                         AngularAccelerometerDataPack (*_getNewReading)());

    int update();

    float getLatestValue();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
    AngularAccelerometerDataPack (*getNewReadingHL)();
    AngularAccelerometerDataPack latestValue;
};

#endif