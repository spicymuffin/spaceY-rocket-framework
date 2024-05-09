#ifndef IACCELEROMETERCONTROL_H
#define IACCELEROMETERCONTROL_H

#include "struct/AccelerometerDataPack.h"

class IAccelerometerControl
{
public:
    const virtual AccelerometerDataPack getAccelerometerReading() { return {}; }
    virtual ~IAccelerometerControl() {}
};

#endif