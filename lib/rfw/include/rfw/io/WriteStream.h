#ifndef __RFW_IO_WRITESTREAM_H
#define __RFW_IO_WRITESTREAM_H

#include <stdarg.h>
#include <stddef.h>

#include "rfw/base/Update.h"

namespace RFW
{
	class WriteStream : public virtual Update
	{
	public:
		virtual size_t io_write(const char *data, size_t size) = 0;
		// virtual size_t __printflike(2, 3) io_writef(const char *format, ...) = 0;
		virtual size_t io_vwritef(const char *format, va_list args) = 0;
		virtual size_t io_flush() = 0;
		virtual ~WriteStream() = default;
	};

	// Wrapper function for WriteStream::io_vwritef
	// Since Pico C/C++ SDK doesn't support variadic arguments in virtual functions,
	// we need to use a wrapper function to call the virtual function with variadic arguments
	size_t io_writef(WriteStream *stream, const char *format, ...);
}

#endif