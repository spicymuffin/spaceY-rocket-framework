#ifndef IACCELEROMETERCONTROL_H
#define IACCELEROMETERCONTROL_H

#include "struct/AccelerometerDataPack.h"

class IAccelerometerControl
{
public:
    const virtual AccelerometerDataPack get_accelerometer_reading() { return {}; }
    virtual ~IAccelerometerControl() {}
};

#endif