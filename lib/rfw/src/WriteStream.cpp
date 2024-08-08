#include "rfw/io/WriteStream.h"

namespace RFW
{
	size_t io_writef(WriteStream *stream, const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		size_t result = stream->io_vwritef(format, args);
		va_end(args);
		return result;
	}
}