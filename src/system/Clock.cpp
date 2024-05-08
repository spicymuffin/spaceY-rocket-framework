#include "system/Clock.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

Clock::Clock(){};

const uint32_t Clock::getNewTimestamp()
{
    this->update();
    return currentTimestamp;
};

const uint32_t Clock::getTimestamp() const
{
    return currentTimestamp;
}

void Clock::update()
{
    currentTimestamp = time_us_32();
}