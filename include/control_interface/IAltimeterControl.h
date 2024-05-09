#ifndef IALTIMETERCONTROL_H
#define IALTIMETERCONTROL_H

class IAltimeterControl
{
public:
    const float getIAltimeterControlReading() { return {}; }
    virtual ~IAltimeterControl() {}
};

#endif