#ifndef IGYROSCOPECONTROL_H
#define IGYROSCOPECONTROL_H

#include "struct/GyroscopeDataPack.h"

class IGyroscopeControl
{
public:
    const virtual GyroscopeDataPack get_gyroscope_reading() { return {}; }
    virtual ~IGyroscopeControl() {}
};

#endif