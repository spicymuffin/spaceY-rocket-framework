#ifndef IACCELEROMETERCONTROL_H
#define IACCELEROMETERCONTROL_H

#include "ext_lib/math3d/math3d.h"

class IAccelerometerControl
{
public:
    const virtual VectorInt16 get_accelerometer_reading() { return {}; }
    virtual ~IAccelerometerControl() {}
};

#endif