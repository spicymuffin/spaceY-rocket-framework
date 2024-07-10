#ifndef IGYROSCOPECONTROL_H
#define IGYROSCOPECONTROL_H

#include "ext_lib/math3d/math3d.h"

class IGyroscopeControl
{
public:
    const virtual VectorInt16 get_gyroscope_reading() { return {}; }
    virtual ~IGyroscopeControl() {}
};

#endif