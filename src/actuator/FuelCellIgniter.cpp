#include "actuator/FuelCellIgniter.h"

#include "param.h"

FuelCellIgniter::FuelCellIgniter(char *_name, int _updateFrequency)
    : RocketModule(_name, _updateFrequency)
{
    // init igniter
}

void FuelCellIgniter::ignite()
{
    // talk to hardware...
}