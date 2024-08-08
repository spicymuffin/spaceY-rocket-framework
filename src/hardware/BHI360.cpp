#include "defs.h"
#include "utils.h"

#include "provider/hardware/BHI360.h"

#include IMU_FIRMWARE_H
#define IMU_FIRMWARE_LEN __CONCAT(IMU_FIRMWARE, _len)

#define WAIT_TRUE 0
#define WAIT_FALSE 1
#define WAIT_NONE 2

#include <string.h>

#include <pico/stdlib.h>
#include <pico/binary_info.h>

#include <hardware/spi.h>

BHI360::BHI360()
{
}

BHI360::~BHI360()
{
}

void BHI360::init()
{
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

	if (!_imu_reset())
	{
		tud_cdc_printf("[ERRR] IMU Reset Failed\n");
		panic("imu reset");
	}

	tud_cdc_printf("[INFO] IMU Reset Success\n");

	uint8_t imu_identifier = _imu_read_reg(0x1C);
	uint8_t imu_revision = _imu_read_reg(0x1D);
	uint8_t rom_revision_lsb = _imu_read_reg(0x1E);
	uint8_t rom_revision_msb = _imu_read_reg(0x1F);

	tud_cdc_printf("[INFO] IMU Identifier: 0x%02X\n", imu_identifier);
	tud_cdc_printf("[INFO] IMU Revision: 0x%02X\n", imu_revision);
	tud_cdc_printf("[INFO] ROM Revision: 0x%02X%02X\n", rom_revision_msb, rom_revision_lsb);

	tud_cdc_printf("[INFO] IMU Reset\n");
	_imu_reset_soft();
	sleep_ms(100);

	uint8_t feature_status = _imu_read_reg(0x24);
	uint8_t boot_status = _imu_read_reg(0x25);

	tud_cdc_printf("[INFO] Feature Status: 0x%02X\n", feature_status);
	tud_cdc_printf("[INFO] Boot Status: 0x%02X\n", boot_status);
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
		if (sensor_id == 0x70 || sensor_id == 0xF0)
		{
			tud_cdc_printf("[INFO] Sensor ID: 0x%X\n", sensor_id);
			return true;
		}
		tud_cdc_printf("[INFO] Sensor ID: 0x%X, expected 0x70 or 0xF0 (%d / %d)\n", sensor_id, count, IMU_SENSOR_TRIES);
	}

	if (count == IMU_SENSOR_TRIES)
	{
		tud_cdc_printf("[INFO] Sensor Soft Reset Failed, trying Hard Reset...\n");
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
		if (sensor_id == 0x70 || sensor_id == 0xF0)
		{
			tud_cdc_printf("[INFO] Sensor ID: 0x%X\n", sensor_id);
			return true;
		}
		tud_cdc_printf("[INFO] Sensor ID: 0x%X, expected 0x70 or 0xF0 (%d / %d)\n", sensor_id, count, IMU_SENSOR_TRIES);
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

	tud_cdc_printf("[INFO] \n");
	tud_cdc_printf("[INFO] Boot Status: 0x%02X\n", status);
	tud_cdc_printf("[INFO] \tInterface: %s\n", interface_ready ? "Ready" : "Not Ready");
	if (firmware_loading)
	{
		tud_cdc_printf("[INFO] \tFirmware: Verification in Progress\n");
	}
	else if (firmware_verify)
	{
		tud_cdc_printf("[INFO] \tFirmware: Verification Success\n");
	}
	else
	{
		tud_cdc_printf("[INFO] \tFirmware: Verification Failed\n");
	}
	tud_cdc_printf("[INFO] \tFirmware State: %s\n\n", firmware_running ? "Running" : "Halted");
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
			tud_cdc_printf("[ERROR] Timeout while waiting for the firmware to load\n");
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
}