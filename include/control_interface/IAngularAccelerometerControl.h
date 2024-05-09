#ifndef IANGULARACCELEROMETERCONTROL_H
#define IANGULARACCELEROMETERCONTROL_H

#include "struct/AngularAccelerometerDataPack.h"

class IAngularAccelerometerControl
{
public:
    const AngularAccelerometerDataPack getAngularAccelerometerReading() { return {}; }
    virtual ~IAngularAccelerometerControl() {}
};

#endif