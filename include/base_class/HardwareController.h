#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "param.h"

class HardwareController
{
public:
    HardwareController(const char* _hardware_name);
    const int get_update_frequency() const;
    virtual const int update();
private:
    int update_frequency;
protected:
    char hardware_name[HARDWARE_MAX_NAME_LEN] = "";
};

#endif