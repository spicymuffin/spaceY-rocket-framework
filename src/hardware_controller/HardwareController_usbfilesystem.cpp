// implementing
#include "hardware_controller/HardwareController_usbfilesystem.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

HardwareController_usbfilesystem::HardwareController_usbfilesystem(const char *_hardwareName)
    : HardwareController(_hardwareName)
{
}

void HardwareController_usbfilesystem::open()
{
}
