#include "base_class/RocketModule.h"

#include "string.h"

char* RocketModule::getName() { return name; };
int RocketModule::getUpdateFrequency() const { return updateFrequency; };

RocketModule::RocketModule(char* _name, int _updateFrequency)
{
    name = _name;
    updateFrequency = _updateFrequency;
};

int RocketModule::update()
{
    printf("default update\n");

    return 0;
}