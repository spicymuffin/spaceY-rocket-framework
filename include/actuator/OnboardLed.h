#ifndef ONBOARDLED_H
#define ONBOARDLED_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// dependencies
#include "control_interface/ILedControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class OnboardLed : public RocketModule, public Actuator
{
public:
    OnboardLed(const char* _name,
        int _update_frequency,
        ILedControl* _ILedController) : RocketModule(_name, _update_frequency),
        Actuator()
    {
        ILedController_ref = _ILedController;
    }
    void set_state(const bool _state)
    {
        return ILedController_ref->set_state(_state);
    }
    void flip_state()
    {
        return ILedController_ref->flip_state();
    }
    bool get_state()
    {
        return ILedController_ref->get_state();
    }
    int update()
    {
        flip_state();
        return 0;
    }

private:
    ILedControl* ILedController_ref;
};

#endif