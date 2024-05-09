#ifndef IACCELEROMETERCONTROL_H
#define IACCELEROMETERCONTROL_H

#include "struct/AccelerometerDataPack.h"

class IAccelerometerControl
{
public:
    const AccelerometerDataPack getAccelerometerReading() { return {}; }
    virtual ~IAccelerometerControl() {}
};

#endif