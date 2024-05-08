#ifndef HARDWARELINK_PICOONBOARDLED_H
#define HARDWARELINK_PICOONBOARDLED_H

#include "param.h"

// base_class
#include "base_class/HardwareLink.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class HardwareLink_picoonboardled : public HardwareLink
{
public:
    HardwareLink_picoonboardled(const char *_hardwareName);
    void picoonboardled_setState(const bool _state);
    void picoonboardled_flipState();
    bool picoonboardled_getState();

private:
    bool state = false;
    unsigned int LED_PIN;
protected:
};

#endif