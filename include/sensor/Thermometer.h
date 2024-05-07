#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <iostream>
#include <string>
#include <vector>

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

using namespace std;

class Thermometer : public RocketModule, public Sensor
{
public:
    /**
     * @brief Construct a new Thermometer object
     *
     * @param _name Thermometer name
     * @param _updateFrequency Thermometer's update frequency
     * @param _textDataSaver Thermometer's data storer (pointer to a TextDataSaver)
     * @param _clock pointer to a Clock object to get timestamps for datapacks
     * @param _getNewReading HardwareLink function that
     */
    Thermometer(string _name,
                int _updateFrequency,
                TextDataSaver *_textDataSaver,
                Clock *_clock,
                float (*_getNewReading)());

    /**
     * @brief
     * get new data, pass it to TextDataSaver and store to buffer
     * @return int update result status
     */
    int update();

    float getLatestValue();

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
    float (*getNewReadingHL)();
    float latestValue;
};

#endif