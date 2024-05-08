#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "param.h"

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

/**
 * @brief
 * contains Altimeter data
 */
struct AltimeterDataPack
{
    double height;
};

class Altimeter : public RocketModule, public Sensor
{
public:
    Altimeter(char *_name,
              int _updateFrequency,
              TextDataSaver *_textDataSaver,
              Clock *_clock);

    int update();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
};

#endif