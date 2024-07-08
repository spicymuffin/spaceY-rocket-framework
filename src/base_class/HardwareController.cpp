#include "base_class/HardwareController.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

HardwareController::HardwareController(const char* _hardware_name)
{
    strcpy(hardware_name, _hardware_name);
}

const int HardwareController::get_update_frequency() const
{
    return update_frequency;
}

const int HardwareController::update()
{
    return -1;
}