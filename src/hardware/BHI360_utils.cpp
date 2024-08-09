#include "defs.h"
#include "utils.h"
#include "provider/hardware/BHI360.h"

#include <string.h>

#include <pico/stdlib.h>

#include <hardware/spi.h>

void BHI360::_list_virtual_sensors()
{
	uint8_t fifo_index = CHANNEL_STATUS_DEBUG_FIFO;
	fifo_index |= 0x80;

	// Clear the Async Status Channel Bit
	uint8_t status = _imu_read_reg(0x06);
	status &= ~0x80;
	_imu_write_reg(0x06, status);

	uint8_t fifo_status = _imu_read_reg(0x2D);
	dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	while (fifo_status & 0x10)
	{
		gpio_put(IMU_SPI_CSn, 0);
		spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
		spi_read_blocking(IMU_SPI_INST, 0, 0, 1);
		gpio_put(IMU_SPI_CSn, 1);
		sleep_ms(10);
		fifo_status = _imu_read_reg(0x2D);
		dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	}

	uint8_t payload[5];
	payload[0] = 0x00;
	payload[1] = 0x11;
	payload[2] = 0x1F;
	payload[3] = 0x00;
	payload[4] = 0x00;

	uint8_t system_data[64];

	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, payload, 5);
	gpio_put(IMU_SPI_CSn, 1);

	fifo_status = _imu_read_reg(0x2D);
	dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	while (fifo_status & 0x10 == 0)
	{
		fifo_status = _imu_read_reg(0x2D);
		dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	}
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
	spi_read_blocking(IMU_SPI_INST, 0, system_data, 64);
	gpio_put(IMU_SPI_CSn, 1);

	_imu_write_reg(0x06, status | 0x80);

	dprintf(_log, "Virtual Sensors Present:\r\n");
	for (int i = 0; i < 64; i++)
	{
		dprintf(_log, "%02X ", system_data[i]);
		if (i % 8 == 7)
		{
			dprintf(_log, "\r\n");
		}
	}
}

void BHI360::_list_physical_sensors()

{
	uint8_t fifo_index = CHANNEL_STATUS_DEBUG_FIFO;
	fifo_index |= 0x80;

	// Clear the Async Status Channel Bit
	uint8_t status = _imu_read_reg(0x06);
	status &= ~0x80;
	_imu_write_reg(0x06, status);

	uint8_t fifo_status = _imu_read_reg(0x2D);
	dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	while (fifo_status & 0x10)
	{
		gpio_put(IMU_SPI_CSn, 0);
		spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
		spi_read_blocking(IMU_SPI_INST, 0, 0, 1);
		gpio_put(IMU_SPI_CSn, 1);
		sleep_ms(10);
		fifo_status = _imu_read_reg(0x2D);
		dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	}

	uint8_t payload[5];
	payload[0] = 0x00;
	payload[1] = 0x11;
	payload[2] = 0x20;
	payload[3] = 0x00;
	payload[4] = 0x00;

	uint8_t system_data[64];

	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, payload, 5);
	gpio_put(IMU_SPI_CSn, 1);

	fifo_status = _imu_read_reg(0x2D);
	dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	while (fifo_status & 0x10 == 0)
	{
		fifo_status = _imu_read_reg(0x2D);
		dprintf(_log, "FIFO Status: 0x%02X\r\n", fifo_status);
	}
	gpio_put(IMU_SPI_CSn, 0);
	spi_write_blocking(IMU_SPI_INST, &fifo_index, 1);
	spi_read_blocking(IMU_SPI_INST, 0, system_data, 64);
	gpio_put(IMU_SPI_CSn, 1);

	_imu_write_reg(0x06, status | 0x80);

	dprintf(_log, "Virtual Sensors Present:\r\n");
	for (int i = 0; i < 64; i++)
	{
		dprintf(_log, "%02X ", system_data[i]);
		if (i % 8 == 7)
		{
			dprintf(_log, "\r\n");
		}
	}

	while (1)
	{
		sleep_ms(1000);
	}
}