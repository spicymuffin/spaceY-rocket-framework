#ifndef ISERVOCONTROL_H
#define ISERVOCONTROL_H

class IServoControl
{
public:
    virtual void setAngle(int _angle) = 0;
};

#endif