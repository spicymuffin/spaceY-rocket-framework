#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <string>
#include <vector>
/// TODO: switch to pico libraries
#include <chrono>

// DEPRECATED BC OF CHANGE TO MICROCONTROLLER (next 4 lines)
// typeid map https://codeforces.com/blog/entry/16101
// ex): typeid(currentTimestampInt).name()

// #include <typeinfo>

using namespace std;

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
     * @param _updateTimestampTarget
     */
    Clock(long long *_updateTimestampTarget);
    /**
     * @brief update and return current timestamp
     *
     * @return long long current timestamp
     */
    long long getNewTimestamp();
    /**
     * @brief get the most recent timestamp
     *
     * @return long long most recent timestamp
     */
    long long getTimestamp();
    /**
     * @brief updates *updateTimestampTarget to current timestamp
     *
     */
    void update();

protected:
private:
    chrono::high_resolution_clock::time_point currentTimestamp;
    long long currentTimestampInt;
    long long *updateTimestampTarget;
};

#endif