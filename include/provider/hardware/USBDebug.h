#ifndef __PROVIDER_HARDWARE_USBDEBUG_H
#define __PROVIDER_HARDWARE_USBDEBUG_H

#include <rfw/io/WriteStream.h>
#include <rfw/io/ReadStream.h>

class USBDebug : public virtual RFW::WriteStream, public virtual RFW::ReadStream
{
public:
	USBDebug();
	virtual ~USBDebug() override;
	void init() override;
	void update() override;
	size_t io_write(const char *data, size_t size) override;
	size_t io_vwritef(const char *format, va_list args) override;
	size_t io_flush() override;

	int8_t io_read_int8(bool sync);
	int16_t io_read_int16(bool sync);
	int32_t io_read_int32(bool sync);
	int64_t io_read_int64(bool sync);
	uint8_t io_read_uint8(bool sync);
	uint16_t io_read_uint16(bool sync);
	uint32_t io_read_uint32(bool sync);
	uint64_t io_read_uint64(bool sync);

	int8_t io_read_fixed_int8(uint8_t length, bool sync);
	int16_t io_read_fixed_int16(uint8_t length, bool sync);
	int32_t io_read_fixed_int32(uint8_t length, bool sync);
	int64_t io_read_fixed_int64(uint8_t length, bool sync);
	uint8_t io_read_fixed_uint8(uint8_t length, bool sync);
	uint16_t io_read_fixed_uint16(uint8_t length, bool sync);
	uint32_t io_read_fixed_uint32(uint8_t length, bool sync);
	uint64_t io_read_fixed_uint64(uint8_t length, bool sync);

	int32_t io_read();
	void io_read_clear();
};

#endif // __PROVIDER_HARDWARE_USBDEBUG_H