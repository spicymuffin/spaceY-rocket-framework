#include "base_class/RocketModule.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

char* RocketModule::getName() { return name; };
int RocketModule::getUpdateFrequency() const { return updateFrequency; };

RocketModule::RocketModule(const char* _name, int _updateFrequency)
{
    strcpy(name, _name);
    updateFrequency = _updateFrequency;
};

int RocketModule::update()
{
    printf("default update\n");

    return 0;
}