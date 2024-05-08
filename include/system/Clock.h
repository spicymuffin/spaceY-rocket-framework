#ifndef CLOCK_H
#define CLOCK_H

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

// DEPRECATED BC OF CHANGE TO MICROCONTROLLER (next 2 lines)
// typeid map https://codeforces.com/blog/entry/16101
// ex): typeid(currentTimestamp).name()

/**
 * @brief
 * Clock manages the timestamp/time related things. crucial to the rocket's
 * control system
 */
class Clock
{
public:
    /**
     * @brief Construct a new Clock object
     *
     */
    Clock();
    /**
     * @brief update and return current timestamp
     *
     * @return uint32_t current timestamp
     */
    const uint32_t getNewTimestamp();
    /**
     * @brief get the most recent cached timestamp
     *
     * @return uint32_t most recent timestamp
     */
    const uint32_t getTimestamp() const;
    /**
     * @brief updates currentTimestamp
     *
     */
    void update();

protected:
private:
    // chrono::high_resolution_clock::time_point currentTimestamp;
    uint32_t currentTimestamp = 0;
};

#endif