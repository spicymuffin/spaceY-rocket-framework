#ifndef ALTIMETER_H
#define ALTIMETER_H

#include <iostream>
#include <string>
#include <vector>

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

using namespace std;

class Altimeter : public RocketModule, public Sensor
{
public:
    /**
     * @brief
     * contains Altimeter data
     */
    struct AltimeterDataPack
    {
        double height;
    };

    /**
     * @brief Construct a new Altimeter object
     *
     * @param _name Altimeter name
     * @param _updateFrequency Altimeter's update frequency
     * @param _textDataSaver Altimeter's data storer (pointer to a TextDataSaver)
     * @param _clock pointer to a Clock object to get timestamps for datapacks
     */
    Altimeter(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock);

    /**
     * @brief
     * get new data, pass it to TextDataSaver and store to buffer
     * @return int update result status
     */
    int update();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
};

#endif