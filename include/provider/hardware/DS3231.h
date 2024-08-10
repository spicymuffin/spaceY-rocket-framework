#ifndef __RFW_HARDWARE_DS3231_H
#define __RFW_HARDWARE_DS3231_H

#include <rfw/clock/AbsoluteClock.h>
#include <rfw/environment/Temperature.h>

#ifndef NDEBUG
#include <memory>

#include <rfw/io/WriteStream.h>
#include <rfw/MetaProvider.hpp>
#endif

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

private:
	uint64_t _time_start;
#ifndef NDEBUG
	std::shared_ptr<RFW::WriteStream> _log;
#endif
};

#endif // __RFW_HARDWARE_DS3231_H