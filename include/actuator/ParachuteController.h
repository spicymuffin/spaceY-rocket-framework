#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include "base_class/RocketModule.h"
#include "base_class/Actuator.h"

class ParachuteController : public RocketModule, public Actuator
{

    /// TODO: add open sensitivity parameter(s)
public:
    ParachuteController(char* _name, int _updateFrequency, IMU *_parachuteIMU);
    void deployParachute();
    int update() override;

private:
    IMU *parachuteIMU;
};

#endif