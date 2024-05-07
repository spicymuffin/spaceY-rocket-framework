#ifndef SENSOR_H
#define SENSOR_H

/**
 * @brief
 * base class for sensors. sensors are rocket modules that record data.
 * // TODO:
 * all sensors should have a method to update their value and a publicly
 * accessible method that returns the last measured value.
 * all sensors should keep a publicly accessible buffer of the last x ticks
 */
class Sensor
{
public:
    Sensor();

protected:
private:
};

#endif