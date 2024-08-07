/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hardware/flash.h>

#include "bsp/board_api.h"
#include "tusb.h"
#include "usb_cdc.h"

int main(void)
{
	board_init();

	usbd_serial_init();

	printf("TinyUSB Host CDC MSC HID Example\r\n");

	// init host stack on configured roothub port
	tuh_init(BOARD_TUH_RHPORT);
	tud_init(BOARD_TUD_RHPORT);

	if (board_init_after_tusb)
	{
		board_init_after_tusb();
	}

	uint64_t last_print = 0;
	while (1)
	{
		tuh_task();
		tud_task();

		if (time_us_64() - last_print > 1000 * 1000)
		{
			last_print = time_us_64();
			tud_cdc_write_str("Hello World!\r\n");
			tud_cdc_write_flush();
		}
	}
}

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

void tuh_mount_cb(uint8_t dev_addr)
{
	// application set-up
	printf("A device with address %d is mounted\r\n", dev_addr);
}

void tuh_umount_cb(uint8_t dev_addr)
{
	// application tear-down
	printf("A device with address %d is unmounted \r\n", dev_addr);
}
