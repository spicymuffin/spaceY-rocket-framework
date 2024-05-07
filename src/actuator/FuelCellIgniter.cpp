#include <iostream>
#include <string>
#include <vector>

#include "FuelCellIgniter.h"

using namespace std;

FuelCellIgniter::FuelCellIgniter(string _name, int _updateFrequency)
    : RocketModule(_name, _updateFrequency)
{
    // init igniter
}

void FuelCellIgniter::ignite()
{
    // talk to hardware...
}