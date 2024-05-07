#ifndef IMU_H
#define IMU_H

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

// TODO: these classes shouldn't cout anyting!

/**
 * @brief
 * IMU (specify model name! different IMUs have different classes!). measures acceleration(s)
 *
 */
class IMU : public RocketModule, public Sensor
{
public:
    /**
     * @brief
     * contains IMU data
     */
    struct IMUDataPack
    {
        double acc_x;
        double acc_y;
        double acc_z;

        double ang_acc_x;
        double ang_acc_y;
        double ang_acc_z;
    };

    /**
     * @brief Construct a new IMU object
     *
     * @param _name IMU name
     * @param _updateFrequency IMU's update frequency
     * @param _textDataSaver IMU's data storer (pointer to a TextDataSaver)
     * @param _clock pointer to a Clock object to get timestamps for datapacks
     */
    IMU(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock);

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