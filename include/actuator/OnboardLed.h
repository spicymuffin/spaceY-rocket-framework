#ifndef ONBOARDLED_H
#define ONBOARDLED_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class OnboardLed : public RocketModule, public Actuator
{
public:
    OnboardLed(const char *_name,
               int _updateFrequency,
               void (*_setState_HL)(const bool _state),
               void (*_flipState_HL)(),
               bool (*_getState_HL)());
    void setState(const bool _state);
    void flipState();
    bool getState();
    int update() { return 0; }

private:
    bool state = false;
    void (*setState_HL)(const bool _state);
    void (*flipState_HL)();
    bool (*getState_HL)();
};

#endif