#include "provider/hardware/DS3231.h"

#include "utils.h"

#include <pico/stdlib.h>
#include <pico/util/datetime.h>

#include <hardware/i2c.h>

uint8_t bcd_to_dec(uint8_t bcd)
{
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

DS3231::DS3231()
{
	i2c_init(i2c1, 100 * 1000);
	gpio_set_function(6, GPIO_FUNC_I2C);
	gpio_set_function(7, GPIO_FUNC_I2C);

	_time_start = 0;
}

void DS3231::init()
{
	uint8_t buf[7] = {
		0,
	};
	i2c_write_blocking(i2c1, 0x68, buf, 1, true);
	i2c_read_blocking(i2c1, 0x68, buf, 7, false);

	buf[0] = bcd_to_dec(buf[0] & 0x7F); // sec
	buf[1] = bcd_to_dec(buf[1] & 0x7F); // min
	buf[2] = bcd_to_dec(buf[2] & 0x3F); // hour
	buf[3] = bcd_to_dec(buf[3] & 0x07); // week
	buf[4] = bcd_to_dec(buf[4] & 0x3F); // day
	buf[5] = bcd_to_dec(buf[5] & 0x1F); // month

	tud_cdc_printf("\r\nRTC: 20%02d-%02d-%02d %02d:%02d:%02d\r\n", buf[6], buf[5], buf[4], buf[2], buf[1], buf[0]);

	// struct datetimte_t dt = {
	// 	.year = buf[6] + 2000,
	// 	.month = buf[5],
	// 	.day = buf[4],
	// 	.dotw = buf[3],
	// 	.hour = buf[2],
	// 	.min = buf[1],
	// 	.sec = buf[0],
	// };

	// _time_start = buf[0] + buf[1] * 60 + buf[2] * 3600 + buf[4] * 86400 + buf[5] * 2678400 + buf[6] * 31536000;
}

double DS3231::get_temperature()
{
	uint8_t buf[3] = {0x11, 0x00, 0x00};
	i2c_write_blocking(i2c1, 0x68, buf, 1, true);
	i2c_read_blocking(i2c1, 0x68, buf + 1, 2, false);

	uint16_t mask = ((1 << 10) - 1) << 6;
	uint16_t value = (buf[1] << 8) | buf[2] & mask >> 6;
	if (value & (1 << 9))
	{
		value -= 2 * 10;
	}

	return value;
}

uint64_t DS3231::get_time_ms()
{
	return 0;
}

uint64_t DS3231::get_time_us()
{
	return 0;
}

void DS3231::set_time(uint64_t time)
{
}
