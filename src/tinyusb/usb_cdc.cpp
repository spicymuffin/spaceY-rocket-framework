#include "bsp/board_api.h"
#include "tusb.h"

#include <hardware/flash.h>

#include "usb_cdc.h"

#define DESC_STR_MAX 20

#define USBD_VID 0x2E8A /* Raspberry Pi */
#define USBD_PID 0x000A /* Raspberry Pi Pico SDK CDC */

#define USBD_STR_0 0x00
#define USBD_STR_MANUF 0x01
#define USBD_STR_PRODUCT 0x02
#define USBD_STR_SERIAL 0x03
#define USBD_STR_SERIAL_LEN 17
#define USBD_STR_CDC 0x04

static const tusb_desc_device_t usbd_desc_device = {
	.bLength = sizeof(tusb_desc_device_t),
	.bDescriptorType = TUSB_DESC_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = TUSB_CLASS_MISC,
	.bDeviceSubClass = MISC_SUBCLASS_COMMON,
	.bDeviceProtocol = MISC_PROTOCOL_IAD,
	.bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
	.idVendor = USBD_VID,
	.idProduct = USBD_PID,
	.bcdDevice = 0x0100,
	.iManufacturer = USBD_STR_MANUF,
	.iProduct = USBD_STR_PRODUCT,
	.iSerialNumber = USBD_STR_SERIAL,
	.bNumConfigurations = 1,
};

const uint8_t *tud_descriptor_device_cb()
{
	return (uint8_t const *)&usbd_desc_device;
}

enum
{
	ITF_NUM_CDC = 0,
	ITF_NUM_CDC_DATA,
	ITF_NUM_TOTAL
};

#define EPNUM_CDC_NOTIF 0x81
#define EPNUM_CDC_OUT 0x02
#define EPNUM_CDC_IN 0x82

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN)

uint8_t const desc_fs_configuration[] = {
	// Config number, interface count, string index, total length, attribute, power in mA
	TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

	// Interface number, string index, EP notification address and size, EP data address (out, in) and size.
	TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
};

#if TUD_OPT_HIGH_SPEED
// Per USB specs: high speed capable device must report device_qualifier and other_speed_configuration

// high speed configuration
uint8_t const desc_hs_configuration[] = {
	// Config number, interface count, string index, total length, attribute, power in mA
	TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

	// Interface number, string index, EP notification address and size, EP data address (out, in) and size.
	TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 512),
};

// other speed configuration
uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];

// device qualifier is mostly similar to device descriptor since we don't change configuration based on speed
tusb_desc_device_qualifier_t const desc_device_qualifier = {
	.bLength = sizeof(tusb_desc_device_qualifier_t),
	.bDescriptorType = TUSB_DESC_DEVICE_QUALIFIER,
	.bcdUSB = USB_BCD,

	.bDeviceClass = TUSB_CLASS_MISC,
	.bDeviceSubClass = MISC_SUBCLASS_COMMON,
	.bDeviceProtocol = MISC_PROTOCOL_IAD,

	.bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
	.bNumConfigurations = 0x01,
	.bReserved = 0x00};

// Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete.
// device_qualifier descriptor describes information about a high-speed capable device that would
// change if the device were operating at the other speed. If not highspeed capable stall this request.
uint8_t const *tud_descriptor_device_qualifier_cb(void)
{
	return (uint8_t const *)&desc_device_qualifier;
}

// Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
// Configuration descriptor in the other speed e.g if high speed then this is for full speed and vice versa
uint8_t const *tud_descriptor_other_speed_configuration_cb(uint8_t index)
{
	(void)index; // for multiple configurations

	// if link speed is high return fullspeed config, and vice versa
	// Note: the descriptor type is OHER_SPEED_CONFIG instead of CONFIG
	memcpy(desc_other_speed_config,
		   (tud_speed_get() == TUSB_SPEED_HIGH) ? desc_fs_configuration : desc_hs_configuration,
		   CONFIG_TOTAL_LEN);

	desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

	return desc_other_speed_config;
}

#endif // highspeed

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
	(void)index; // for multiple configurations

#if TUD_OPT_HIGH_SPEED
	// Although we are highspeed, host may be fullspeed.
	return (tud_speed_get() == TUSB_SPEED_HIGH) ? desc_hs_configuration : desc_fs_configuration;
#else
	return desc_fs_configuration;
#endif
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// String Descriptor Index
enum
{
	STRID_LANGID = 0,
	STRID_MANUFACTURER,
	STRID_PRODUCT,
	STRID_SERIAL,
};

// array of pointer to string descriptors
char const *string_desc_arr[] = {
	(const char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
	"TinyUSB",					// 1: Manufacturer
	"TinyUSB Device",			// 2: Product
	NULL,						// 3: Serials will use unique ID if possible
	"TinyUSB CDC",				// 4: CDC Interface
};

static uint16_t _desc_str[32 + 1];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
	(void)langid;
	size_t chr_count;

	switch (index)
	{
	case STRID_LANGID:
		memcpy(&_desc_str[1], string_desc_arr[0], 2);
		chr_count = 1;
		break;

	case STRID_SERIAL:
		chr_count = board_usb_get_serial(_desc_str + 1, 32);
		break;

	default:
		// Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
		// https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

		if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0])))
			return NULL;

		const char *str = string_desc_arr[index];

		// Cap at max char
		chr_count = strlen(str);
		size_t const max_count = sizeof(_desc_str) / sizeof(_desc_str[0]) - 1; // -1 for string type
		if (chr_count > max_count)
			chr_count = max_count;

		// Convert ASCII string into UTF-16
		for (size_t i = 0; i < chr_count; i++)
		{
			_desc_str[1 + i] = str[i];
		}
		break;
	}

	// first byte is length (including header), second byte is string type
	_desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

	return _desc_str;
}

static char usbd_serial[USBD_STR_SERIAL_LEN] = "000000000000";
void usbd_serial_init(void)
{
	uint8_t id[8];
	flash_get_unique_id(id);
	snprintf(usbd_serial, USBD_STR_SERIAL_LEN, "%02X%02X%02X%02X%02X%02X%02X%02X",
			 id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7]);
}