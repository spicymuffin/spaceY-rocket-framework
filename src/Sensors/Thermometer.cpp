#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "RocketModule.h"
#include "Actuator.h"
#include "TextDataSaver.h"
#include "Clock.h"

#include "Thermometer.h"

Thermometer::Thermometer(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock, float (*_getLatestValueHL)()) : RocketModule(_name, _updateFrequency)
{
    textDataSaver = _textDataSaver;
    clock = _clock;
    getNewReadingHL = _getLatestValueHL;
};

int Thermometer::update()
{
    cout << name << " update" << endl;

    // TODO: get data from IMU, parse, organize

    latestValue = (*getNewReadingHL)();

#pragma region format and dump
    long long ts = clock->getTimestamp();

    // // std::format and fmt format (std requires C++20)
    // // format("{:.2f}", 3.14159265359); // s == "3.14"

    // string dumpString = fmt::format("{:.2f}", 3.14159265359);
    // textDataSaver->dumpLine(dumpString);
#pragma endregion
    return 0;
};

float Thermometer::getLatestValue()
{
    return latestValue;
}