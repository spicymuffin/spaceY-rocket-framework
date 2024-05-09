#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "param.h"

class HardwareController
{
public:
    HardwareController(const char *_hardwareName);

private:
protected:
    char hardwareName[HARDWARE_MAX_NAME_LEN] = "";
};

#endif