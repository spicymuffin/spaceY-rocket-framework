#ifndef IALTIMETERCONTROL_H
#define IALTIMETERCONTROL_H

class IAltimeterControl
{
public:
    const float getAltimeterReading() { return 0; }
    virtual ~IAltimeterControl() {}
};

#endif