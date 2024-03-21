#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <iostream>
#include <string>
#include <vector>

#include "RocketModule.h"
#include "Sensor.h"
#include "TextDataSaver.h"
#include "Clock.h"

using namespace std;

class Gyroscope : public RocketModule, public Sensor
{
public:
    /**
     * @brief
     * contains Gyroscope data
     */
    struct GyroscopeDataPack
    {
        double x;
        double y;
        double z;
    };

    /**
     * @brief Construct a new Gyroscope object
     *
     * @param _name Gyroscope name
     * @param _updateFrequency Gyroscope's update frequency
     * @param _textDataSaver Gyroscope's data storer (pointer to a TextDataSaver)
     * @param _clock pointer to a Clock object to get timestamps for datapacks
     */
    Gyroscope(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock);

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