#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "RocketModule.h"
#include "Actuator.h"
#include "TextDataSaver.h"

using namespace std;

//TODO: these classes shouldn't cout anyting!

class IMU : public RocketModule, public Actuator
{
public:
    IMU(string _name, int _updateFrequency, TextDataSaver *_textDataSaver) : RocketModule(_name, _updateFrequency)
    {
        textDataSaver = _textDataSaver;
    };

    int update()
    {
        cout << name << " update" << endl;

        //TODO: get data from IMU, parse, organize

        textDataSaver->dumpLine("a");
        return 0;
    };

private:
    TextDataSaver *textDataSaver;
};