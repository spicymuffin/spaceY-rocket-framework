#ifndef __RFW_IO_READSTREAM_H
#define __RFW_IO_READSTREAM_H

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include "rfw/base/Base.h"

namespace RFW
{
	class ReadStream : public virtual Base
	{
	public:
		virtual int8_t io_read_int8(bool sync) = 0;
		virtual int16_t io_read_int16(bool sync) = 0;
		virtual int32_t io_read_int32(bool sync) = 0;
		virtual int64_t io_read_int64(bool sync) = 0;
		virtual uint8_t io_read_uint8(bool sync) = 0;
		virtual uint16_t io_read_uint16(bool sync) = 0;
		virtual uint32_t io_read_uint32(bool sync) = 0;
		virtual uint64_t io_read_uint64(bool sync) = 0;

		virtual int8_t io_read_fixed_int8(uint8_t length, bool sync) = 0;
		virtual int16_t io_read_fixed_int16(uint8_t length, bool sync) = 0;
		virtual int32_t io_read_fixed_int32(uint8_t length, bool sync) = 0;
		virtual int64_t io_read_fixed_int64(uint8_t length, bool sync) = 0;
		virtual uint8_t io_read_fixed_uint8(uint8_t length, bool sync) = 0;
		virtual uint16_t io_read_fixed_uint16(uint8_t length, bool sync) = 0;
		virtual uint32_t io_read_fixed_uint32(uint8_t length, bool sync) = 0;
		virtual uint64_t io_read_fixed_uint64(uint8_t length, bool sync) = 0;

		virtual int32_t io_read() = 0;

		virtual void io_read_clear() = 0;
		virtual ~ReadStream() = default;
	};
}

#endif // __RFW_IO_READSTREAM_H