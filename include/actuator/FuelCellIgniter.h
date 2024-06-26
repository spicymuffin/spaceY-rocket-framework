#ifndef FUELCELLIGNITER_H
#define FUELCELLIGNITER_H

#include "param.h"

// base_class
#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

// dependencies

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

class FuelCellIgniter : public RocketModule, public Actuator
{
public:
    FuelCellIgniter(const char *_name,
                    int _updateFrequency) : RocketModule(_name, _updateFrequency),
                                            Actuator()
    {
    }
    void ignite()
    {
    }
    void getIgnitionState()
    {
    }
    int update() { return 0; }

private:
};

#endif