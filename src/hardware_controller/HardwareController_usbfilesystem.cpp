// implementing
#include "hardware_controller/HardwareController_usbfilesystem.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "hardware/dma.h" // rewrite with dma use?

// dependcies

HardwareController_usbfilesystem::HardwareController_usbfilesystem(
    const char* _hardware_name,
    int _update_frequency)

    :

    HardwareController(_hardware_name, _update_frequency)
{

}

void HardwareController_usbfilesystem::open()
{

}

const int HardwareController_usbfilesystem::update()
{
    return 0;
}