#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "RocketModule.h"
#include "Sensor.h"

using namespace std;

/**
 * @brief
 * takes picutures.
 */
class Camera : public RocketModule, public Sensor
{
public:
    Camera(string _name, int _updateFrequency, string _directoryPath, string _fileNamePostfix);

    int update() { return 0; };

private:
};

#endif