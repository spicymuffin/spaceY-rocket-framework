#include "provider/software/LogWriter.h"

#include <rfw/MetaProvider.hpp>

LogWriter::LogWriter()
{
	_file = nullptr;
	_error = FR_OK;
}

void LogWriter::init()
{
	auto metaProvider = RFW::MetaProvider::getInstance();
	_clock = metaProvider.getBestProvider<RFW::AbsoluteClock>(RFW::GetLast<RFW::AbsoluteClock>);
	_filesystem = metaProvider.getProvider<RFW::FileSystem>("USBStorage");
}

LogWriter::~LogWriter()
{
	if (_file)
	{
		f_close(_file);
	}
}

FRESULT LogWriter::open(const char *path, uint8_t mode)
{
	if (!_filesystem)
	{
		return FR_NOT_ENABLED;
	}

	return f_open(_file, path, mode);
}

FRESULT LogWriter::close()
{
	if (!_filesystem)
	{
		return FR_NOT_ENABLED;
	}

	return f_close(_file);
}

FRESULT LogWriter::flush()
{
	if (!_filesystem)
	{
		return FR_NOT_ENABLED;
	}

	return f_sync(_file);
}

FRESULT LogWriter::error() const
{
	return _error;
}

size_t LogWriter::io_write(const char *data, size_t size)
{
	if (!_filesystem)
	{
		return -1;
	}

	UINT bytesWritten;
	_error = f_write(_file, data, size, &bytesWritten);

	return bytesWritten;
}

// size_t __printflike(2, 3) LogWriter::io_writef(const char *format, ...)
// {
// 	if (!_filesystem)
// 	{
// 		return -1;
// 	}
//
// 	va_list args;
// 	va_start(args, format);
// 	size_t bytesWritten = io_vwritef(format, args);
// 	va_end(args);
//
// 	return bytesWritten;
// }

size_t LogWriter::io_vwritef(const char *format, va_list args)
{
	if (!_filesystem)
	{
		return -1;
	}

	char buffer[256];
	size_t bytesWritten = vsnprintf(buffer, sizeof(buffer), format, args);

	UINT bytesWritten2;
	_error = f_write(_file, buffer, bytesWritten, &bytesWritten2);

	return bytesWritten2;
}

bool LogWriter::is_open() const
{
	return _file != nullptr;
}

size_t LogWriter::io_flush()
{
	if (!_filesystem)
	{
		return -1;
	}

	return f_sync(_file);
}

void LogWriter::update()
{
	// if (_clock)
	// {
	// 	_clock->update();
	// }
}