#ifndef IALTIMETERCONTROL_H
#define IALTIMETERCONTROL_H

class IAltimeterControl
{
public:
    const float get_altimeter_reading() { return 0; }
    virtual ~IAltimeterControl() {}
};

#endif