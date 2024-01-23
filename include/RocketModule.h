#ifndef ROCKETMODULE_H
#define ROCKETMODULE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief
 * rocket module base class. all rocket's modules that are not crucial to the
 * operation of the rocket's control system are rocket modules
 *
 * a ServoMotor is an actuator: rocket module: it performs actions like moving its
 * control "arm"
 *
 * a TextDataSaver is an (virtual) actuator: it saves data to the memory of the flight computer
 *
 * a GPS module is a sensor: it determines the rocket's position but cannot perform actions
 * with that data
 *
 * an IMU is a sensor: it determines the rocket's accelerations but cannot perform actions
 * with that data
 */
class RocketModule
{
public:
    /**
     * @brief Construct a new RocketModule object
     *
     * @param _name name of module
     * @param _updateFrequency update frequency of module (set -1 to imply make module non-updating)
     */
    RocketModule(string _name, int _updateFrequency);
    /**
     * @brief Get name the RocketModule
     *
     * @return string name of the RocketModule
     */
    string getName();
    /**
     * @brief Get update frequency of the RocketModule
     *
     * @return int update frequency of the RocketModule
     */
    int getUpdateFrequency() const;
    /**
     * @brief execute RocketModule's code
     *
     * @return int update result
     */
    virtual int update();

protected:
    int tick;
    int updateFrequency;
    string name;

private:
};

#endif