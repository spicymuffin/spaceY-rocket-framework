#ifndef ILEDCONTROL_H
#define ILEDCONTROL_H

class ILedControl
{
public:
    virtual void set_state(const bool _state) = 0;
    virtual void flip_state() = 0;
    virtual const bool get_state() = 0;
    virtual ~ILedControl() {}
};

#endif