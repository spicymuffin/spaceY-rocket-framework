// implementing
#include "actuator/OnboardLed.h"

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

OnboardLed::OnboardLed(
    const char* _name,
    int _update_frequency,
    ILedControl* _ILedController)

    :

    RocketModule(_name, _update_frequency),
    Actuator()
{
    ILedController_ref = _ILedController;
}

void OnboardLed::set_state(const bool _state)
{
    return ILedController_ref->set_state(_state);
}

void OnboardLed::flip_state()
{
    return ILedController_ref->flip_state();
}

bool OnboardLed::get_state()
{
    return ILedController_ref->get_state();
}

const int OnboardLed::update()
{
    flip_state();
    return 0;
}