#ifndef __RFW_HARDWARE_BHI360_H
#define __RFW_HARDWARE_BHI360_H

#include <rfw/base/Update.h>
#include <rfw/clock/AbsoluteClock.h>
#include <rfw/environment/Temperature.h>
#include <rfw/environment/Pressure.h>

#ifndef NDEBUG
#include <memory>

#include <rfw/io/WriteStream.h>
#include <rfw/MetaProvider.hpp>
#endif

class BHI360 : public virtual RFW::Temperature, public virtual RFW::Pressure, public virtual RFW::Update
{
public:
	BHI360();
	virtual ~BHI360() override;
	void init() override;
	double get_temperature() override;
	double get_pressure() override;
	void update() override;

private:
	bool _imu_reset();
	void _imu_reset_soft();
	void _imu_reset_hard();
	uint8_t _imu_read_reg(uint8_t);
	void _imu_write_reg(uint8_t, uint8_t);
	void _imu_write_data(uint8_t, uint8_t *, uint8_t);
	void _print_status(uint8_t);
	bool _poll_status(uint8_t, uint8_t, uint64_t check_interval = 1000, uint64_t check_timeout = 5000);

#ifndef NDEBUG
	std::shared_ptr<RFW::WriteStream> _log;
#endif
};

#endif // __RFW_HARDWARE_BHI360_H