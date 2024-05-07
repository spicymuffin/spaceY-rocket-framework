#ifndef FUELCELLIGNITER_H
#define FUELCELLIGNITER_H

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

class FuelCellIgniter : public RocketModule, public Actuator
{
public:
    FuelCellIgniter(char* _name, int _updateFrequency);
    void ignite();
    int update() { return 0; }

private:
};

#endif