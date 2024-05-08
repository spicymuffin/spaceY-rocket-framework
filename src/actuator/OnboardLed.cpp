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

OnboardLed::OnboardLed(const char *_name,
                       int _updateFrequency,
                       void (*_setState_HL)(const bool _state),
                       void (*_flipState_HL)(),
                       bool (*_getState_HL)())
    : RocketModule(_name, _updateFrequency),
      Actuator()
{
    strcpy(name, _name);
    updateFrequency = _updateFrequency;
    setState_HL = _setState_HL;
    flipState_HL = _flipState_HL;
    getState_HL = _getState_HL;
}

void OnboardLed::setState(const bool _state)
{
    return (*setState_HL)(_state);
}

void OnboardLed::flipState()
{
    return (*flipState_HL)();
}

bool OnboardLed::getState()
{
    return (*getState_HL)();
}