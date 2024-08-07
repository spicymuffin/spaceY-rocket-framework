#include "defs.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <pico/platform.h>
#include <pico/multicore.h>
#include <pico/runtime.h>
#include <pico/sync.h>

#include "tusb.h"

auto_init_mutex(serial_mutex);

bool core1_panic = false;
char core1_panic_message[2048] = {
	0,
};

int32_t tud_cdc_buffer[SERIAL_BUFFER_SIZE];
uint32_t tud_cdc_buffer_head = 0;
uint32_t tud_cdc_buffer_tail = 0;

void tud_cdc_vprintf(const char *fmt, va_list args)
{
	char message[2048];
	memset(message, 0, sizeof(message));

	// size_t len = vsnprintf(NULL, 0, fmt, args) + 1;

	va_list args2;
	va_copy(args2, args);
	vsprintf(message, fmt, args2);
	va_end(args2);

	tud_cdc_write_str(message);
	tud_cdc_write_flush();
	tud_task();
}

void __printflike(1, 0) tud_cdc_printf(const char *fmt, ...)
{
	mutex_enter_blocking(&serial_mutex);

	va_list args;
	va_start(args, fmt);
	tud_cdc_vprintf(fmt, args);
	va_end(args);

	mutex_exit(&serial_mutex);
}

void __attribute__((noreturn)) __printflike(1, 0) tusb_panic(const char *fmt, ...)
{
	if (get_core_num() == 1)
	{
		va_list args1, args2;
		va_start(args1, fmt);

		// size_t len = vsnprintf(NULL, 0, fmt, args1) + 1;
		va_end(args1);

		memset(core1_panic_message, 0, sizeof(core1_panic_message));
		vsprintf(core1_panic_message, fmt, args2);
		va_end(args2);

		core1_panic = true;

		multicore_reset_core1();
		while (true)
		{
			tight_loop_contents();
		}
	}

	if (core1_panic)
	{
		tud_cdc_write_str("\r\n\r\npanic: core1 panic\r\n");

		if (core1_panic_message[0])
		{
			tud_cdc_write_str(core1_panic_message);
		}

		while (true)
		{
			tight_loop_contents();
		}
	}
	else
	{
		tud_cdc_write_str("\r\n\r\npanic: core0 panic\r\n");
		va_list args;
		va_start(args, fmt);
		tud_cdc_vprintf(fmt, args);

		while (true)
		{
			tud_task();
			tuh_task();
		}
	}
}

void tud_cdc_buffer_init()
{
	memset(tud_cdc_buffer, 0, sizeof(tud_cdc_buffer));
}

int32_t tud_cdc_buffer_read()
{
	if (tud_cdc_buffer_head == tud_cdc_buffer_tail)
	{
		return -1;
	}

	int32_t c = tud_cdc_buffer[tud_cdc_buffer_head];
	tud_cdc_buffer_head = (tud_cdc_buffer_head + 1) % SERIAL_BUFFER_SIZE;
	return c;
}

void tud_cdc_buffer_write(int32_t c)
{
	if ((tud_cdc_buffer_tail + 1) % SERIAL_BUFFER_SIZE == tud_cdc_buffer_head)
	{
		return;
	}
	tud_cdc_buffer[tud_cdc_buffer_tail] = c;
	tud_cdc_buffer_tail = (tud_cdc_buffer_tail + 1) % SERIAL_BUFFER_SIZE;
}

void tud_cdc_buffer_flush()
{
	tud_cdc_buffer_head = 0;
	tud_cdc_buffer_tail = 0;
}

int8_t tud_cdc_buffer_get_int8(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int8_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

int16_t tud_cdc_buffer_get_int16(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int16_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

int32_t tud_cdc_buffer_get_int32(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int32_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

uint8_t tud_cdc_buffer_get_uint8(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint8_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

uint16_t tud_cdc_buffer_get_uint16(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint16_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

uint32_t tud_cdc_buffer_get_uint32(bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint32_t value = 0;
	while (true)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			continue;
		}

		if (c == '\n' || c == '\r')
		{
			break;
		}
	}

	return value;
}

int8_t tud_cdc_buffer_get_fixed_int8(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int8_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}

int16_t tud_cdc_buffer_get_fixed_int16(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int16_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}

int32_t tud_cdc_buffer_get_fixed_int32(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	int32_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}

uint8_t tud_cdc_buffer_get_fixed_uint8(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint8_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}

uint16_t tud_cdc_buffer_get_fixed_uint16(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint16_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}

uint32_t tud_cdc_buffer_get_fixed_uint32(uint8_t target, bool flush)
{
	if (flush)
	{
		tud_cdc_buffer_flush();
	}

	uint32_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = tud_cdc_buffer_read();
		if (c == -1)
		{
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			value = value * 10 + (c - '0');
			length++;
			continue;
		}
	}

	return value;
}
