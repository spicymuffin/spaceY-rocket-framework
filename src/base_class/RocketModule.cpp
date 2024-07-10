#include "base_class/RocketModule.h"

#include "param.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"

char* RocketModule::get_name() { return name; };
int RocketModule::get_update_frequency() const { return update_frequency; };

RocketModule::RocketModule(const char* _name, int _update_frequency)
{
    strcpy(name, _name);
    update_frequency = _update_frequency;
};

const int RocketModule::update()
{
    printf("undefined rm update\n");

    return 0;
}