#ifndef __RFW_IO_WRITESTREAM_H
#define __RFW_IO_WRITESTREAM_H

#include "rfw/base/Update.h"

namespace RFW
{
	class WriteStream : public virtual Update
	{
	public:
		virtual size_t io_write(const char *data, size_t size) = 0;
		virtual size_t io_writef(const char *format, ...) = 0;
		virtual size_t io_flush() = 0;
		virtual ~WriteStream() = default;
	};
}

#endif