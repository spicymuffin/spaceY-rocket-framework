#include "defs.h"

#include "provider/hardware/USBDebug.h"

#include <pico/bootrom.h>
#include <pico/multicore.h>

#include <hardware/watchdog.h>

#include "bsp/board_api.h"
#include "tusb.h"
#include "usb.h"

int32_t _buffer[USB_DEVICE_BUFFER_SIZE];
int32_t _buffer_write_index = 0;
int32_t _buffer_read_index = 0;

void preinit()
{
	while (true)
	{
		tud_task();
	}
}

USBDebug::USBDebug()
{
}

USBDebug::~USBDebug()
{
}

void USBDebug::init()
{
	usbd_serial_init();
	tud_init(BOARD_TUD_RHPORT);

	// This is DEBUG, so we should always do the tud task
	multicore_reset_core1();
	multicore_launch_core1(preinit);

#if DEBUG_START_PAUSE
	uint64_t last_print = 0;

	io_read_clear();
	while (true)
	{
		if (time_us_64() - last_print > 1000 * 1000)
		{
			tud_cdc_write_str("Press any key to continue\r\n");
			tud_cdc_write_flush();
			last_print = time_us_64();
		}

		tuh_task();
		tud_task();

		int32_t c = io_read();
		if (c != -1)
		{
			break;
		}
	}
#endif
}

size_t USBDebug::io_write(const char *data, size_t size)
{
	return tud_cdc_write(data, size);
}

size_t USBDebug::io_vwritef(const char *format, va_list args)
{
	va_list args2;
	va_copy(args2, args);
	size_t size = vsnprintf(NULL, 0, format, args);
	char *buffer = new char[size + 1];
	vsnprintf(buffer, size + 1, format, args2);
	size_t written = io_write(buffer, size);
	delete[] buffer;
	va_end(args2);

	return written;
}

size_t USBDebug::io_flush()
{
	return tud_cdc_write_flush();
}

void USBDebug::update()
{
	tud_task();
}

int32_t USBDebug::io_read()
{
	if (_buffer_read_index == _buffer_write_index)
	{
		return -1;
	}

	int32_t c = _buffer[_buffer_read_index];
	_buffer_read_index = (_buffer_read_index + 1) % USB_DEVICE_BUFFER_SIZE;
	return c;
}

void USBDebug::io_read_clear()
{
	_buffer_read_index = 0;
	_buffer_write_index = 0;
}

int8_t USBDebug::io_read_int8(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int8_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

int16_t USBDebug::io_read_int16(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int16_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

int32_t USBDebug::io_read_int32(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int32_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

int64_t USBDebug::io_read_int64(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int64_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

uint8_t USBDebug::io_read_uint8(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint8_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

uint16_t USBDebug::io_read_uint16(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint16_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

uint32_t USBDebug::io_read_uint32(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint32_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

uint64_t USBDebug::io_read_uint64(bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint64_t value = 0;
	while (true)
	{
		int32_t c = io_read();
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

int8_t USBDebug::io_read_fixed_int8(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int8_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

int16_t USBDebug::io_read_fixed_int16(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int16_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

int32_t USBDebug::io_read_fixed_int32(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int32_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

int64_t USBDebug::io_read_fixed_int64(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	int64_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

uint8_t USBDebug::io_read_fixed_uint8(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint8_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

uint16_t USBDebug::io_read_fixed_uint16(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint16_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

uint32_t USBDebug::io_read_fixed_uint32(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint32_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

uint64_t USBDebug::io_read_fixed_uint64(uint8_t target, bool flush)
{
	if (flush)
	{
		io_read_clear();
	}

	uint64_t value = 0;
	uint8_t length = 0;
	while (length < target)
	{
		int32_t c = io_read();
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

void tud_cdc_rx_cb(uint8_t itf)
{
	(void)itf; // no-op

	char buf[512];
	uint32_t count = tud_cdc_read(buf, sizeof(buf));

	for (int i = 0; i < count; ++i)
	{
		if (buf[i] == 0x03) // Ctrl-C
		{
			watchdog_enable(0, 0);
			while (1)
				;
		}

		if (buf[i] == 0x04) // Ctrl-D
		{
			reset_usb_boot(0, 0);
			while (1)
				;
		}

		if ((_buffer_write_index + 1) % USB_DEVICE_BUFFER_SIZE == _buffer_read_index)
		{
			return;
		}
		_buffer[USB_DEVICE_BUFFER_SIZE] = buf[i];
		_buffer_write_index = (_buffer_write_index + 1) % USB_DEVICE_BUFFER_SIZE;
		tud_cdc_write_char(buf[i]);
	}
	tud_cdc_write_flush();
}
