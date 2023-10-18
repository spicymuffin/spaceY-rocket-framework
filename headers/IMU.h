#pragma once

#include <iostream>
#include <string>
#include <vector>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "RocketModule.h"
#include "Actuator.h"
#include "TextDataSaver.h"
#include "Clock.h"

using namespace std;

// TODO: these classes shouldn't cout anyting!

class IMU : public RocketModule, public Actuator
{
public:
    struct IMUDataPack
    {
        double acc_x;
        double acc_y;
        double acc_z;

        double ang_acc_x;
        double ang_acc_y;
        double ang_acc_z;
    };

    IMU(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock) : RocketModule(_name, _updateFrequency)
    {
        textDataSaver = _textDataSaver;
        clock = _clock;
    };

    int update()
    {
        cout << name << " update" << endl;

        // TODO: get data from IMU, parse, organize

        IMUDataPack dataPack;
        // blah blah blah, write to data pack

#pragma region format and dump
        long long ts = clock->getTimestamp();

        // std::format and fmt format (std requires C++20)
        // format("{:.2f}", 3.14159265359); // s == "3.14"

        string dumpString = fmt::format("{:.2f}", 3.14159265359);
        textDataSaver->dumpLine(dumpString);

#pragma endregion
        return 0;
    };

private:
    TextDataSaver *textDataSaver;
    Clock *clock;
};