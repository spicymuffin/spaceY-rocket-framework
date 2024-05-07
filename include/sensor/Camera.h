#ifndef CAMERA_H
#define CAMERA_H

#include "base_class/RocketModule.h"
#include "base_class/Sensor.h"


/**
 * @brief
 * takes picutures.
 */
class Camera : public RocketModule, public Sensor
{
public:
    Camera(char* _name, int _updateFrequency, char* _directoryPath, char* _fileNamePostfix);

    int update() { return 0; };

private:
};

#endif