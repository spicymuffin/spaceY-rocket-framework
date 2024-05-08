#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "param.h"

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

struct AccelerometerDataPack
{
    double acc_x;
    double acc_y;
    double acc_z;
};

class Accelerometer : public RocketModule, public Sensor
{
public:
    Accelerometer(char *_name,
                  int _updateFrequency,
                  TextDataSaver *_textDataSaver,
                  Clock *_clock);

    int update();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
};

#endif