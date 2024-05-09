#ifndef IGYROSCOPECONTROL_H
#define IGYROSCOPECONTROL_H

#include "struct/GyroscopeDataPack.h"

class IGyroscopeControl
{
public:
    const GyroscopeDataPack getGyroscopeReading() { return {}; }
    virtual ~IGyroscopeControl() {}
};

#endif