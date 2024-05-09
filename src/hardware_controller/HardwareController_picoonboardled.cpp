// implementing
#include "hardware_controller/HardwareController_picoonboardled.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
HardwareController_picoonboardled::HardwareController_picoonboardled(const char *_hardwareName)
    : HardwareController(_hardwareName)
{
    LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}
#endif

void HardwareController_picoonboardled::setState(const bool _state)
{
    if (_state)
    {
        gpio_put(LED_PIN, 1);
    }
    else
    {
        gpio_put(LED_PIN, 0);
    }
    state = _state;
}

void HardwareController_picoonboardled::flipState()
{
    if (state)
    {
        gpio_put(LED_PIN, 0);
        state = false;
    }
    else
    {
        gpio_put(LED_PIN, 1);
        state = true;
    }
}
bool HardwareController_picoonboardled::getState()
{
    return state;
}
