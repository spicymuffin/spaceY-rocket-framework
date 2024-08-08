#ifndef __RFW_HARDWARE_BHI360_H
#define __RFW_HARDWARE_BHI360_H

#include <rfw/clock/AbsoluteClock.h>
#include <rfw/environment/Temperature.h>
#include <rfw/environment/Pressure.h>

class BHI360 : public virtual RFW::Temperature, public virtual RFW::Pressure
{
public:
	BHI360();
	virtual ~BHI360() override;
	void init() override;
};

#endif // __RFW_HARDWARE_BHI360_H