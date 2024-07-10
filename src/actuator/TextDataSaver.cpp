// implementing
#include "actuator/TextDataSaver.h"

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

TextDataSaver::TextDataSaver(const char* _name,
    int _update_frequency,
    const char* _directory_path,
    const char* _filename_postfix,
    IFileSystemContol* _IFileSystemContoller)

    :

    RocketModule(_name, _update_frequency),
    Actuator()
{
    IFileSystemContoller = _IFileSystemContoller;
}

void TextDataSaver::dumpLine(char* _line)
{
    /// TODO: dump line using filesystem
}

const int TextDataSaver::update()
{
    return 0;
}