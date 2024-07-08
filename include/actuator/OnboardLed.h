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
        int _updateFrequency,
        ILedControl* _ILedController) : RocketModule(_name, _updateFrequency),
        Actuator()
    {
        ILedController_ref = _ILedController;
    }
    void setState(const bool _state)
    {
        return ILedController_ref->setState(_state);
    }
    void flipState()
    {
        return ILedController_ref->flipState();
    }
    bool getState()
    {
        return ILedController_ref->getState();
    }
    int update()
    {
        flipState();
        return 0;
    }

private:
    ILedControl* ILedController_ref;
};

#endif