#ifndef TEXTDATASAVER_H
#define TEXTDATASAVER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// dependencies
#include "control_interface/IFileSystemContol.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class TextDataSaver : public RocketModule,
    public Actuator
{
public:
    TextDataSaver(const char* _name,
        int _updateFrequency,
        const char* _directoryPath,
        const char* _fileNamePostfix,
        IFileSystemContol* _IFileSystemContoller) : RocketModule(_name, _updateFrequency),
        Actuator()
    {
        IFileSystemContoller = _IFileSystemContoller;
    }

    void dumpLine(char* _line)
    {
        /// TODO: dump line using filesystem
    }

    int update()
    {
        return 0;
    };

private:
    /// TODO: fix filesystem
    IFileSystemContol* IFileSystemContoller;
    char* dumpFilePath;
    char* directoryPath;
};

#endif