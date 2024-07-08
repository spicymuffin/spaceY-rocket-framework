#ifndef ILEDCONTROL_H
#define ILEDCONTROL_H

class ILedControl
{
public:
    virtual void setState(const bool _state) = 0;
    virtual void flipState() = 0;
    virtual const bool getState() = 0;
    virtual ~ILedControl() {}
};

#endif