#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// set updateFrequency to -1 to make it an not updating module.

class RocketModule
{
public:
    RocketModule(string _name, int _updateFrequency)
    {
        name = _name;
        updateFrequency = _updateFrequency;
    };

    string getName()
    {
        return name;
    };

protected:
    int tick;
    int updateFrequency;
    string name;
    virtual int update()
    {
        cout << "default update" << endl;

        return 0;
    }

private:
};
