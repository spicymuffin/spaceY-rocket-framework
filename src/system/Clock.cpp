#include "system/Clock.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

Clock::Clock() {};

const uint32_t Clock::get_new_ts()
{
    this->update();
    return current_ts;
};

const uint32_t Clock::get_ts() const
{
    return current_ts;
}

void Clock::update()
{
    current_ts = time_us_32();
}