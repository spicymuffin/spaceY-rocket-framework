// implementing
#include "hardware_controller/HardwareController_picoonboardled.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#ifdef RASPBERRYPI_PICO_W
#include "pico/cyw43_arch.h"
#endif

#if defined(RASPBERRYPI_PICO_W)
HardwareController_picoonboardled::HardwareController_picoonboardled(
    const char *_hardware_name,
    int _update_frequency)
    : HardwareController(_hardware_name, _update_frequency)
{
    if (!cyw43_arch_async_context())
    {
        cyw43_arch_init();
    }
    LED_PIN = (uint)-1;
}
#elif defined(RASPBERRYPI_PICO)
HardwareController_picoonboardled::HardwareController_picoonboardled(
    const char *_hardware_name,
    int _update_frequency)

    :

      HardwareController(_hardware_name, _update_frequency)
{
    LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}
#else
#error "Board not supported"
#endif

void HardwareController_picoonboardled::set_state(const bool _state)
{
    if (_state)
    {
#ifdef RASPBERRYPI_PICO
        gpio_put(LED_PIN, 1);
#elif defined(RASPBERRYPI_PICO_W)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
#endif
    }
    else
    {
#ifdef RASPBERRYPI_PICO
        gpio_put(LED_PIN, 0);
#elif defined(RASPBERRYPI_PICO_W)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
#endif
    }
    state = _state;
}

void HardwareController_picoonboardled::flip_state()
{
    if (state)
    {
#ifdef RASPBERRYPI_PICO
        gpio_put(LED_PIN, 0);
#elif defined(RASPBERRYPI_PICO_W)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
#endif
        state = false;
    }
    else
    {
#ifdef RASPBERRYPI_PICO
        gpio_put(LED_PIN, 1);
#elif defined(RASPBERRYPI_PICO_W)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
#endif
        state = true;
    }
}

const bool HardwareController_picoonboardled::get_state()
{
    return state;
}

const int HardwareController_picoonboardled::update()
{
    return 0;
}