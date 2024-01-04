#ifndef Clock_H
#define Clock_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// typeid map https://codeforces.com/blog/entry/16101
// ex): typeid(currentTimestampInt).name()

#include <typeinfo>

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