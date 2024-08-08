#ifndef __PROVIDER_HARDWARE_USBDEBUG_H
#define __PROVIDER_HARDWARE_USBDEBUG_H

#include <rfw/io/WriteStream.h>

class USBDebug : public virtual RFW::WriteStream
{
public:
	USBDebug();
	virtual ~USBDebug() override;
	void init() override;
	void update() override;
	size_t io_write(const char *data, size_t size) override;
	size_t io_vwritef(const char *format, va_list args) override;
	size_t io_flush() override;
};

#endif // __PROVIDER_HARDWARE_USBDEBUG_H