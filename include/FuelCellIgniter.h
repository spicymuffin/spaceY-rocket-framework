#ifndef FUELCELLIGNITER_H
#define FUELCELLIGNITER_H

#include <iostream>
#include <string>
#include <vector>

#include "RocketModule.h"
#include "Actuator.h"

class FuelCellIgniter : public RocketModule, public Actuator
{
public:
    FuelCellIgniter(string _name, int _updateFrequency);
    void ignite();
    int update() { return 0; }

private:
};

#endif