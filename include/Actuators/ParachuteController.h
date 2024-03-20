#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include <iostream>
#include <string>
#include <vector>

#include "RocketModule.h"
#include "Actuator.h"
#include "IMU.h"

using namespace std;

class ParachuteController : public RocketModule, public Actuator
{

    /// TODO: add open sensitivity parameter(s)
public:
    ParachuteController(string _name, int _updateFrequency, IMU *_parachuteIMU);
    void deployParachute();
    int update() override;

private:
    IMU *parachuteIMU;
};

#endif