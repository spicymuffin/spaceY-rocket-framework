// implementing
#include "hardware_link/HardwareLink_picoonboardled.h"

#include "param.h"

// base_class
#include "base_class/HardwareLink.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
HardwareLink_picoonboardled::HardwareLink_picoonboardled(const char *_hardwareName) : HardwareLink(_hardwareName)
{
    LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}
#endif

void HardwareLink_picoonboardled::picoonboardled_setState(const bool _state)
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

void HardwareLink_picoonboardled::picoonboardled_flipState()
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
bool HardwareLink_picoonboardled::picoonboardled_getState()
{
    return state;
}
