#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <iostream>
#include <string>
#include <vector>

#include "RocketModule.h"
#include "Sensor.h"
#include "TextDataSaver.h"
#include "Clock.h"

using namespace std;

class Accelerometer : public RocketModule, public Sensor
{
public:
    /**
     * @brief
     * contains Acceleromter data
     */
    struct AccelerometerDataPack
    {
        double acc_x;
        double acc_y;
        double acc_z;
    };

    /**
     * @brief Construct a new Accelerometer object
     *
     * @param _name Accelerometer name
     * @param _updateFrequency Accelerometer's update frequency
     * @param _textDataSaver Accelerometer's data storer (pointer to a TextDataSaver)
     * @param _clock pointer to a Clock object to get timestamps for datapacks
     */
    Accelerometer(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock);

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