#ifndef __USB_CDC_H
#define __USB_CDC_H

#define USB_BOARD_INITIALIZED 0x1
#define USB_HOST_INITIALIZED 0x2
#define USB_DEVICE_INITIALIZED 0x4

extern int usb_init_status;

void usbd_serial_init();

#endif // __USB_CDC_H