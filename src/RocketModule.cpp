#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "RocketModule.h"

string RocketModule::getName() { return name; };
int RocketModule::getUpdateFrequency() const { return updateFrequency; };

RocketModule::RocketModule(string _name, int _updateFrequency)
{
    name = _name;
    updateFrequency = _updateFrequency;
};

int RocketModule::update()
{
    cout << "default update" << endl;

    return 0;
}