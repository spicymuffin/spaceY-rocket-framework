#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "RocketModule.h"
#include "Actuator.h"

using namespace std;

class TextDataSaver : public RocketModule, public Actuator
{
public:
    TextDataSaver(string _name, int _updateFrequency) : RocketModule(_name, _updateFrequency)
    {
        cout << "asd" << endl;
    };

    int update()
    {
        cout << name << " update" << endl;

        return 0;
    }
};