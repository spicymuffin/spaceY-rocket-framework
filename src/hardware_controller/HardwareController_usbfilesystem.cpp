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

HardwareController_usbfilesystem::HardwareController_usbfilesystem(const char* _hardwareName)
    : HardwareController(_hardwareName)
{

}

const int HardwareController_usbfilesystem::update()
{
    return 0;
}