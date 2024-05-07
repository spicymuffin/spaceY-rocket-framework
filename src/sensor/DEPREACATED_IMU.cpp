#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"
#include "actuator/TextDataSaver.h"
#include "system/Clock.h"

IMU::IMU(string _name, int _updateFrequency, TextDataSaver *_textDataSaver, Clock *_clock) : RocketModule(_name, _updateFrequency)
{
    textDataSaver = _textDataSaver;
    clock = _clock;
};

int IMU::update()
{
    printf(name << " update");

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
