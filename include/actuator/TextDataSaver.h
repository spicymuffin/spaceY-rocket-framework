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
        int _update_frequency,
        const char* _directory_path,
        const char* _filename_postfix,
        IFileSystemContol* _IFileSystemContoller);

    void dumpLine(char* _line);
    const int update() override;
private:
    /// TODO: fix filesystem
    IFileSystemContol* IFileSystemContoller;
    char* filepath;
    char* dirpath;
};

#endif