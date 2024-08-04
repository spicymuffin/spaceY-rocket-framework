#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "param.h"

#define SDA_PIN 20
#define SCL_PIN 21

class HardwareController
{
public:
    HardwareController(const char* _hardware_name, int _update_frequency);
    const int get_update_frequency() const;
    virtual const int update();
private:
    int update_frequency;
protected:
    char hardware_name[HARDWARE_MAX_NAME_LEN] = "";
};

#endif