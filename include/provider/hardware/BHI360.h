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

#define WAIT_TRUE 0
#define WAIT_FALSE 1
#define WAIT_NONE 2

#define CHANNEL_WAKEUP_FIFO 0x01
#define CHANNEL_NON_WAKEUP_FIFO 0x02
#define CHANNEL_STATUS_DEBUG_FIFO 0x03

typedef struct
{
	uint16_t length;
	uint8_t data[32];
} fifo_data_t;

#define FIFO_BUFFER_SIZE 64

typedef struct
{
	uint16_t rindex;
	uint16_t windex;
	fifo_data_t data[FIFO_BUFFER_SIZE];
} fifo_buffer_t;

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
	uint16_t _imu_read_fifo(uint8_t, uint8_t[32]);
	void _imu_write_fifo(uint8_t, uint8_t[32], uint16_t);
	void _imu_start_sensor(uint8_t);
	uint64_t _sensor_task();
	void _process_fifo(uint8_t fifo_index);
	fifo_buffer_t fifo_data[3];
#ifndef NDEBUG
	void _list_virtual_sensors();
	void _list_physical_sensors();

	std::shared_ptr<RFW::WriteStream> _log;
#endif
};

#endif // __RFW_HARDWARE_BHI360_H