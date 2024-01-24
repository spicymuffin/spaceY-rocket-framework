#ifndef IMAGEDATASAVER_H
#define IMAGEATASAVER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "RocketModule.h"
#include "Actuator.h"

using namespace std;

/**
 * @brief
 * saves image data to a file.
 */
class ImageDataSaver : public RocketModule, public Actuator
{
public:
    ImageDataSaver(string _name, int _updateFrequency, string _directoryPath, string _fileNamePostfix);

    void dumpImage();

    int update() { return 0; };

private:
    ofstream dumpFile;
    string dumpFilePath;
    string directoryPath;
};

#endif