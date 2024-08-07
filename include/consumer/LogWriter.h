#ifndef __RFW_CONSUMER_LOGWRITER_H
#define __RFW_CONSUMER_LOGWRITER_H

#include <stddef.h>
#include <stdarg.h>
#include <memory>

#include <pico/stdlib.h>

#include <rfw/filesystem/FileSystem.h>

#include <ff.h>

class LogWriter
{
public:
	LogWriter();

	FRESULT open(const char *path, uint8_t mode);
	FRESULT close();
	FRESULT flush();
	FRESULT error() const;

	size_t write(const char *data, size_t size);
	size_t __printflike(2, 3) writef(const char *format, ...);

	bool is_open() const;

	virtual ~LogWriter();

private:
	FIL *_file;
	FRESULT _error;
	std::shared_ptr<RFW::FileSystem> _filesystem;

	size_t vwritef(const char *format, va_list args);
};

#endif // __RFW_CONSUMER_LOGWRITER_H