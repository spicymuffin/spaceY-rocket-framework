#include "provider/hardware/USBDebug.h"

#include "bsp/board_api.h"
#include "tusb.h"
#include "usb.h"

USBDebug::USBDebug()
{
}

USBDebug::~USBDebug()
{
}

void USBDebug::init()
{
	if (usb_init_status & USB_BOARD_INITIALIZED == 0)
	{
		board_init();
		if (board_init_after_tusb)
		{
			board_init_after_tusb();
		}
		usb_init_status |= USB_BOARD_INITIALIZED;
	}

	if (usb_init_status & USB_DEVICE_INITIALIZED == 0)
	{
		usbd_serial_init();
		tud_init(BOARD_TUD_RHPORT);
		usb_init_status |= USB_DEVICE_INITIALIZED;
	}
}

size_t USBDebug::io_write(const char *data, size_t size)
{
	return 0;
}

size_t USBDebug::io_vwritef(const char *format, va_list args)
{
	return 0;
}

size_t USBDebug::io_flush()
{
	return 0;
}

void USBDebug::update()
{
	tud_task();
}