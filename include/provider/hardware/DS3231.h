#ifndef __RFW_HARDWARE_DS3231_H
#define __RFW_HARDWARE_DS3231_H

#include <rfw/clock/AbsoluteClock.h>
#include <rfw/environment/Temperature.h>

class DS3231 : public virtual RFW::AbsoluteClock, public virtual RFW::Temperature
{
public:
	DS3231();
	virtual ~DS3231() override = default;
	void init() override;
	double get_temperature() override;
	uint64_t get_time_ms() override;
	uint64_t get_time_us() override;
	void set_time(uint64_t time) override;
};

#endif // __RFW_HARDWARE_DS3231_H