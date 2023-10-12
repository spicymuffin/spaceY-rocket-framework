#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// typeid map https://codeforces.com/blog/entry/16101
// ex): typeid(currentTimestampInt).name()
#include <typeinfo>

using namespace std;

class Clock
{
public:
    Clock(long long *_updateTimestampTarget) : updateTimestampTarget(_updateTimestampTarget){};
    ~Clock(){};
    long long getTimestamp()
    {
        currentTimestamp = chrono::high_resolution_clock::now();
        auto now_microseconds = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimestamp);
        currentTimestampInt = now_microseconds.time_since_epoch().count();
        return currentTimestampInt;
    };
    void update()
    {
        currentTimestamp = chrono::high_resolution_clock::now();
        auto now_microseconds = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimestamp);

        // is a long long
        // TODO: chage it to long, so no need to store time from epoch...
        currentTimestampInt = now_microseconds.time_since_epoch().count();

        *updateTimestampTarget = currentTimestampInt;
    }

protected:
private:
    chrono::high_resolution_clock::time_point currentTimestamp;
    long long currentTimestampInt;
    long long *updateTimestampTarget;
};