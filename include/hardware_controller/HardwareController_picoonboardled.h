#ifndef HARDWARECONTROLLER_PICOONBOARDLED_H
#define HARDWARECONTRELLER_PICOONBOARDLED_H

#include "param.h"

// base_class
#include "base_class/HardwareController.h"
#include "actuator/OnboardLed.h"

// implements
#include "control_interface/ILedControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class HardwareController_picoonboardled
    : public HardwareController,
    public ILedControl
{
public:
    HardwareController_picoonboardled(const char* _hardwareName);
    void set_state(const bool _state) override;
    void flip_state() override;
    const bool get_state() override;
    const int update() override;

private:
    bool state = false;
    unsigned int LED_PIN;

protected:
};

#endif