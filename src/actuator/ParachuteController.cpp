#include "actuator/ParachuteController.h"

ParachuteController::ParachuteController(char* _name,
                                         int _updateFrequency,
                                         IMU *_parachuteIMU)
    : RocketModule(_name, _updateFrequency)
{
    parachuteIMU = _parachuteIMU;
}

void ParachuteController::deployParachute()
{
    // depoloy parachute
}

int ParachuteController::update()
{
    // if (parachute should be opened)
    // this->deployParachute();
}