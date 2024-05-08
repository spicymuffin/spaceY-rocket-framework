#ifndef HARDWARELINK_H
#define HARDWARELINK_H

#include "param.h"

class HardwareLink
{
public:
    HardwareLink(const char *_hardwareName);

private:
protected:
    char hardwareName[HARDWARE_MAX_NAME_LEN] = "";
};

#endif