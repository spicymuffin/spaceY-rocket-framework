#ifndef IMAGEDATASAVER_H
#define IMAGEATASAVER_H

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

/**
 * @brief
 * saves image data to a file.
 */
class ImageDataSaver : public RocketModule, public Actuator
{
public:
    ImageDataSaver(char* _name, int _updateFrequency, char* _directoryPath, char* _fileNamePostfix);

    void dumpImage();

    int update() { return 0; };

private:
    ofstream dumpFile;
    char* dumpFilePath;
    char* directoryPath;
};

#endif