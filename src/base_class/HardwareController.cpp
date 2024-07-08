#include "base_class/HardwareController.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

HardwareController::HardwareController(const char *_hardwareName)
{
    strcpy(hardwareName, _hardwareName);
}

const int HardwareController::getUpdateFrequency() const{
    return updateFrequency;
}