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

// dependencies
#include "control_interface/ILedControl.h"

class OnboardLed : public RocketModule, public Actuator
{
public:
    OnboardLed(const char* _name, int _update_frequency, ILedControl* _ILedController);
    void set_state(const bool _state);
    void flip_state();
    bool get_state();
    const int update() override;

private:
    ILedControl* ILedController_ref;
};

#endif