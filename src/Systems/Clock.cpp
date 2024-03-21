#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Clock.h"

Clock::Clock(long long *_updateTimestampTarget) : updateTimestampTarget(_updateTimestampTarget){};

long long Clock::getNewTimestamp()
{ 
    currentTimestamp = chrono::high_resolution_clock::now();
    auto now_microseconds = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimestamp);
    currentTimestampInt = now_microseconds.time_since_epoch().count();
    return currentTimestampInt;
};

long long Clock::getTimestamp()
{
    return currentTimestampInt;
}

void Clock::update()
{
    currentTimestamp = chrono::high_resolution_clock::now();
    auto now_microseconds = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimestamp);

    // is a long long
    /// TODO: chage it to long, so no need to store time from epoch...
    currentTimestampInt = now_microseconds.time_since_epoch().count();

    *updateTimestampTarget = currentTimestampInt;
}