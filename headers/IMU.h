#include <iostream>
#include <string>
#include <vector>
#include "RocketModule.h"
#include "Actuator.h"
#include "TextDataSaver.h"

using namespace std;

class IMU : public RocketModule, public Actuator
{
public:
    IMU(string _name, int _updateFrequency) : RocketModule(_name, _updateFrequency)
    {
        cout << "asd" << endl;
    };

    int update()
    {
        cout << name << " update" << endl;

        return 0;
    }
};