#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

struct GyroscopeDataPack
{
    double x;
    double y;
    double z;
};

class Gyroscope : public RocketModule, public Sensor
{
public:
    Gyroscope(const char *_name,
              int _updateFrequency,
              TextDataSaver *_textDataSaver,
              Clock *_clock);

    int update();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
    GyroscopeDataPack (*getNewReadingHL)();
    GyroscopeDataPack latestValue;
};

#endif