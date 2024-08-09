#include "defs.h"
#include "utils.h"

#include "provider/hardware/BHI360.h"

#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>
#include <pico/binary_info.h>

#include <hardware/spi.h>

#include IMU_FIRMWARE_H
#define IMU_FIRMWARE_LEN __CONCAT(IMU_FIRMWARE, _len)

BHI360::BHI360()
{
	for (int i = 0; i < 3; i++)
	{
		fifo_data[i].rindex = 0;
		fifo_data[i].windex = 0;
		for (int j = 0; j < FIFO_BUFFER_SIZE; j++)
		{
			fifo_data[i].data[j].length = 0;
			memset(fifo_data[i].data[j].data, 0, 32);
		}
	}
}

BHI360::~BHI360()
{
}

void BHI360::init()
{
#ifndef NDEBUG
	RFW::MetaProvider &provider = RFW::MetaProvider::getInstance();
	_log = provider.getProvider<RFW::WriteStream>("DEBUG");
#endif

	spi_init(IMU_SPI_INST, 1000 * 1000);
	spi_set_format(IMU_SPI_INST, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
	gpio_set_function(IMU_SPI_MISO, GPIO_FUNC_SPI);
	gpio_set_function(IMU_SPI_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(IMU_SPI_SCK, GPIO_FUNC_SPI);

	gpio_init(IMU_SPI_CSn);
	gpio_set_dir(IMU_SPI_CSn, GPIO_OUT);
	gpio_put(IMU_SPI_CSn, 1);

	gpio_init(IMU_RESET);
	gpio_set_dir(IMU_RESET, GPIO_OUT);

	bi_decl(bi_4pins_with_func(IMU_SPI_MISO, IMU_SPI_MOSI, IMU_SPI_SCK, IMU_SPI_CSn, GPIO_FUNC_SPI));
	bi_decl(bi_1pin_with_name(IMU_RESET, "IMU Reset"));

	dprintf(_log, "[INFO] IMU Init\r\n");

	if (!_imu_reset())
	{
		dprintf(_log, "[ERRR] IMU Reset Failed\r\n");
		panic("imu reset");
	}

	dprintf(_log, "[INFO] IMU Reset Success\r\n");

	uint8_t imu_identifier = _imu_read_reg(0x1C);
	uint8_t imu_revision = _imu_read_reg(0x1D);
	uint8_t rom_revision_lsb = _imu_read_reg(0x1E);
	uint8_t rom_revision_msb = _imu_read_reg(0x1F);

	dprintf(_log, "[INFO] IMU Identifier: 0x%02X\r\n", imu_identifier);
	dprintf(_log, "[INFO] IMU Revision: 0x%02X\r\n", imu_revision);
	dprintf(_log, "[INFO] ROM Revision: 0x%02X%02X\r\n", rom_revision_msb, rom_revision_lsb);

	uint8_t feature_status = _imu_read_reg(0x24);
	uint8_t boot_status = _imu_read_reg(0x25);

	dprintf(_log, "[INFO] Feature Status: 0x%02X\r\n", feature_status);
	dprintf(_log, "[INFO] Boot Status: 0x%02X\r\n", boot_status);

	_imu_write_reg(0x14, 0x01);
	_imu_write_reg(0x05, 0x00);
	_imu_write_reg(0x06, 0x00);
	_imu_write_reg(0x07, 0x00);

	if (!_poll_status(WAIT_TRUE, WAIT_NONE))
	{
		panic("imu status: interface");
	}

	dprintf(_log, "[INFO] Loading Firmware...\r\n");
	uint8_t payload[5];

	payload[0] = 0x00;
	payload[1] = 0x02;
	payload[2] = 0x00;

	uint16_t fw_len = IMU_FIRMWARE_LEN / 4;
	payload[3] = fw_len & 0xFF;
	payload[4] = (fw_len >> 8) & 0xFF;

	dprintf(_log, "[INFO] Command Length: 5\r\n");
	dprintf(_log, "[INFO] Firmware Length: %d\r\n", IMU_FIRMWARE_LEN);
	dprintf(_log, "[INFO] Total Length: %d\r\n", 5 + IMU_FIRMWARE_LEN);
	dprintf(_log, "\r\n");

	// TODO: Fix here if the ram is not enough
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, payload, 5);
	spi_write_blocking(IMU_SPI_INST, IMU_FIRMWARE, IMU_FIRMWARE_LEN);
	gpio_put(IMU_SPI_CSn, 1);

	dprintf(_log, "[INFO] Verifying Firmware\r\n");
	_poll_status(WAIT_NONE, WAIT_TRUE, 1000, 60 * 1000);

	dprintf(_log, "[INFO] Starting Firmware\r\n");
	payload[0] = 0x00;
	payload[1] = 0x03;
	payload[2] = 0x00;
	payload[3] = 0x00;
	payload[4] = 0x00;

	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, payload, 5);
	gpio_put(IMU_SPI_CSn, 1);

	_poll_status(WAIT_FALSE, WAIT_NONE);
	_poll_status(WAIT_TRUE, WAIT_NONE);

	uint64_t initalized = 0;
	while (initalized < 2)
	{
		initalized += _sensor_task();
		dprintf(_log, "Processed %d task(s)\r\n", initalized);
	}

	sleep_ms(100);
	dprintf(_log, "\r\n[INFO] Sensor Initialized\r\n");
	sleep_ms(100);

	_imu_start_sensor(0x04); // Accelerometer
	_imu_start_sensor(0x0D); // Gyroscope
	_imu_start_sensor(0x16); // Magnetometer
	_imu_start_sensor(0x80); // Temperature
	_imu_start_sensor(0x81); // Barometer

	while (true)
	{
		_sensor_task();
	}
}

bool BHI360::_imu_reset()
{
	int count = 0;

	_imu_reset_soft();

	if (!_poll_status(WAIT_TRUE, WAIT_NONE))
	{
		panic("imu status: interface");
	}

	while (count < IMU_SENSOR_TRIES)
	{
		count++;

		uint8_t sensor_id = _imu_read_reg(0x2B);
#if defined(IMU_SENSOR_ID1) && !defined(IMU_SENSOR_ID2)
		if (sensor_id == IMU_SENSOR_ID1)
		{
			dprintf(_log, "[INFO] Sensor ID: 0x%X\r\n", sensor_id);
			return true;
		}
		dprintf(_log, "[INFO] Sensor ID: 0x%X, expected 0x%02X (%d / %d)\r\n", sensor_id, IMU_SENSOR_ID1, count, IMU_SENSOR_TRIES);
#elif defined(IMU_SENSOR_ID1) && defined(IMU_SENSOR_ID2)
		if (sensor_id == IMU_SENSOR_ID1 || sensor_id == IMU_SENSOR_ID2)
		{
			dprintf(_log, "[INFO] Sensor ID: 0x%X\r\n", sensor_id);
			return true;
		}
		dprintf(_log, "[INFO] Sensor ID: 0x%X, expected 0x%02X or 0x%02X (%d / %d)\r\n", sensor_id, IMU_SENSOR_ID1, IMU_SENSOR_ID2, count, IMU_SENSOR_TRIES);
#else
#error "IMU_SENSOR_ID1 must be defined"
#endif
	}

	if (count == IMU_SENSOR_TRIES)
	{
		dprintf(_log, "[INFO] Sensor Soft Reset Failed, trying Hard Reset...\r\n");
	}

	_imu_reset_hard();

	if (!_poll_status(WAIT_TRUE, WAIT_NONE))
	{
		panic("imu status: interface");
	}

	_imu_reset_soft();

	count = 0;
	while (count < IMU_SENSOR_TRIES)
	{
		count++;

		uint8_t sensor_id = _imu_read_reg(0x2B);
#if defined(IMU_SENSOR_ID1) && !defined(IMU_SENSOR_ID2)
		if (sensor_id == IMU_SENSOR_ID1)
		{
			dprintf(_log, "[INFO] Sensor ID: 0x%X\r\n", sensor_id);
			return true;
		}
		dprintf(_log, "[INFO] Sensor ID: 0x%X, expected 0x%02X (%d / %d)\r\n", sensor_id, IMU_SENSOR_ID1, count, IMU_SENSOR_TRIES);
#elif defined(IMU_SENSOR_ID1) && defined(IMU_SENSOR_ID2)
		if (sensor_id == IMU_SENSOR_ID1 || sensor_id == IMU_SENSOR_ID2)
		{
			dprintf(_log, "[INFO] Sensor ID: 0x%X\r\n", sensor_id);
			return true;
		}
		dprintf(_log, "[INFO] Sensor ID: 0x%X, expected 0x%02X or 0x%02X (%d / %d)\r\n", sensor_id, IMU_SENSOR_ID1, IMU_SENSOR_ID2, count, IMU_SENSOR_TRIES);
#else
#error "IMU_SENSOR_ID1 must be defined"
#endif
	}

	return false;
}

void BHI360::_imu_reset_soft()
{
	_imu_write_reg(0x14, 0x01);
	sleep_ms(100);
}

void BHI360::_imu_reset_hard()
{
	gpio_put(IMU_RESET, 0);
	sleep_ms(10);
	gpio_put(IMU_RESET, 1);
	sleep_ms(10);
}

uint8_t BHI360::_imu_read_reg(uint8_t address)
{
	uint8_t buffer;
	address |= 0x80; // Read command
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, &address, 1);
	spi_read_blocking(IMU_SPI_INST, 0, &buffer, 1);
	gpio_put(IMU_SPI_CSn, 1);
	return buffer;
}

void BHI360::_imu_write_reg(uint8_t address, uint8_t value)
{
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, &address, 1);
	spi_write_blocking(IMU_SPI_INST, &value, 1);
	gpio_put(IMU_SPI_CSn, 1);
}

void BHI360::_imu_write_data(uint8_t reg, uint8_t *data, uint8_t len)
{
	uint8_t buffer[257];
	buffer[0] = reg;
	memcpy(&buffer[1], data, len);

	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, buffer, len + 1);
	gpio_put(IMU_SPI_CSn, 1);
}

void BHI360::_print_status(uint8_t status)
{
	bool interface_ready = (status & 0x10) != 0;
	bool firmware_loading = (status & 0x20) == 0;
	bool firmware_verify = (status & 0x40) == 0;
	bool firmware_running = (status & 0x80) == 0;

	dprintf(_log, "[INFO] \r\n");
	dprintf(_log, "[INFO] Boot Status: 0x%02X\r\n", status);
	dprintf(_log, "[INFO] \tInterface: %s\r\n", interface_ready ? "Ready" : "Not Ready");
	if (firmware_loading)
	{
		dprintf(_log, "[INFO] \tFirmware: Verification in Progress\r\n");
	}
	else if (firmware_verify)
	{
		dprintf(_log, "[INFO] \tFirmware: Verification Success\r\n");
	}
	else
	{
		dprintf(_log, "[INFO] \tFirmware: Verification Failed\r\n");
	}
	dprintf(_log, "[INFO] \tFirmware State: %s\r\n\n", firmware_running ? "Running" : "Halted");
}

bool BHI360::_poll_status(uint8_t check_ready, uint8_t check_verify, uint64_t print_interval_ms, uint64_t timeout_ms)
{
	uint64_t time_last_print = 0;
	uint64_t time_check_start = time_us_64();
	while (true)
	{
		uint8_t status = _imu_read_reg(0x25);
		bool interface_ready = (status & 0x10) != 0;
		bool firmware_loading = (status & 0x20) == 0;
		bool firmware_verify = (status & 0x40) == 0;
		bool firmware_running = (status & 0x80) == 0;

		bool verified = !firmware_loading && firmware_verify;

		if (time_us_64() - time_last_print > print_interval_ms * 1000)
		{
			_print_status(status);
			time_last_print = time_us_64();
		}

		if (time_us_64() - time_check_start > timeout_ms * 1000)
		{
			dprintf(_log, "[ERROR] Timeout while waiting for the firmware to load\r\n");
			return false;
		}

		if (check_verify != WAIT_NONE && !firmware_loading && ((check_verify == WAIT_TRUE) == verified))
		{
			_print_status(status);
			return true;
		}

		if (check_ready != WAIT_NONE && ((check_ready == WAIT_TRUE) == interface_ready))
		{
			_print_status(status);
			return true;
		}
	}
}

double BHI360::get_pressure()
{
	return 0;
}

double BHI360::get_temperature()
{
	return -297.15;
}

void BHI360::update()
{
	_sensor_task();
}

uint64_t BHI360::_sensor_task()
{
	uint8_t messages = 0;

	uint8_t intr = _imu_read_reg(0x2D);

	if (intr & 0x01 == 0)
	{
		return 0;
	}

	uint8_t wakeup_status = (intr >> 1) & 0x03;
	uint8_t nwakeup_status = (intr >> 3) & 0x03;
	uint8_t debug_status = (intr >> 6) & 0x01;

	if (wakeup_status != 0)
	{
		_process_fifo(CHANNEL_WAKEUP_FIFO);
		messages++;
	}

	if (nwakeup_status != 0)
	{
		_process_fifo(CHANNEL_NON_WAKEUP_FIFO);
		messages++;
	}

	if (debug_status != 0)
	{
		_process_fifo(CHANNEL_STATUS_DEBUG_FIFO);
		messages++;
	}

	return messages;
}

void BHI360::_process_fifo(uint8_t fifo_index)
{
	fifo_buffer_t *buffer = fifo_data + (fifo_index - 1);

	uint32_t read_length = 0;

	fifo_index = fifo_index | 0x80; // Read command

	dprintf(_log, "Reading FIFO %d\r\n", fifo_index - 0x80);

	uint8_t data_size_buf[2];
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
	spi_read_blocking(IMU_SPI_INST, 0, data_size_buf, 2);
	gpio_put(IMU_SPI_CSn, 1);

	uint16_t data_size = data_size_buf[0] | (data_size_buf[1] << 8);
	if (data_size == 0)
	{
		return;
	}

	dprintf(_log, "FIFO %d Size: %d\r\n", fifo_index - 0x80, data_size);

	uint16_t data_read = 0;
	while (data_read < data_size)
	{
		uint16_t remainder = data_size - data_read;
		buffer->data[buffer->windex].length = remainder > 32 ? 32 : remainder;

		dprintf(_log, "Reading %d bytes from FIFO %d\r\n", remainder, fifo_index - 0x80);

		gpio_put(IMU_SPI_CSn, 0);
		spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
		spi_read_blocking(IMU_SPI_INST, 0, buffer->data[buffer->windex].data, buffer->data[buffer->windex].length);
		gpio_put(IMU_SPI_CSn, 1);

		dprintf(_log, "\r\n");
		for (int i = 0; i < data_size; ++i)
		{
			dprintf(_log, "%02X ", buffer->data[buffer->windex].data[i]);
		}
		dprintf(_log, "\r\n");

		data_read += buffer->data[buffer->windex].length;
		buffer->windex = (buffer->windex + 1) % FIFO_BUFFER_SIZE;
	}
}

uint16_t BHI360::_imu_read_fifo(uint8_t fifo_index, uint8_t fifo_buffer[32])
{
	fifo_buffer_t *buffer = fifo_data + (fifo_index - 1);

	if (buffer->rindex == buffer->windex)
	{
		return (uint16_t)-1;
	}

	uint16_t length = buffer->data[buffer->rindex].length;
	memcpy(fifo_buffer, buffer->data[buffer->rindex].data, 32);

	buffer->rindex = (buffer->rindex + 1) % FIFO_BUFFER_SIZE;

	return length;
}

void BHI360::_imu_write_fifo(uint8_t fifo_index, uint8_t fifo_buffer[32], uint16_t length)
{
	fifo_buffer_t *buffer = fifo_data + (fifo_index - 1);

	if ((buffer->windex + 1) % FIFO_BUFFER_SIZE == buffer->rindex)
	{
		return;
	}

	buffer->data[buffer->windex].length = length;
	memcpy(buffer->data[buffer->windex].data, fifo_buffer, 32);

	buffer->windex = (buffer->windex + 1) % FIFO_BUFFER_SIZE;
}

void BHI360::_imu_start_sensor(uint8_t sensor_id)
{
	float rate = 100;

	uint8_t sensor_init[13];
	sensor_init[0] = 0x00;

	sensor_init[1] = 0x0D; // 0x00
	sensor_init[2] = 0x00; // 0x01

	sensor_init[3] = 0x08; // 0x02
	sensor_init[4] = 0x00; // 0x03

	sensor_init[5] = sensor_id; // 0x04 BHY2_SENSOR_ID_ACC

	sensor_init[6] = (uint32_t)rate & 0xFF;			// 0x05
	sensor_init[7] = ((uint32_t)rate >> 8) & 0xFF;	// 0x06
	sensor_init[8] = ((uint32_t)rate >> 16) & 0xFF; // 0x07
	sensor_init[9] = ((uint32_t)rate >> 24) & 0xFF; // 0x08

	sensor_init[10] = 0x00; // 0x09
	sensor_init[11] = 0x00; // 0x0A
	sensor_init[12] = 0x00; // 0x0B

	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, sensor_init, 13);
	gpio_put(IMU_SPI_CSn, 1);
}