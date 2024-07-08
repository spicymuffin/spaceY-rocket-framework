#ifndef ISERVOCONTROL_H
#define ISERVOCONTROL_H

class IServoControl
{
public:
    virtual void set_angle(int _angle) = 0;
};

#endif