#ifndef HARDWARECONTROLLER_SERVOTYPE0_H
#define HARDWARECONTROLLER_SERVOTYPE0_H

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// implements
#include "control_interface/IServoControl.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class HardwareController_servotype0 : public HardwareController,
    public IServoControl
{
public:
    HardwareController_servotype0(char* _hardwaremodelName);
    void set_angle(int _angle) override;

private:
protected:
};

#endif