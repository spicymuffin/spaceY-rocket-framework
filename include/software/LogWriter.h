#ifndef __RFW_SOFTWARE_LOGWRITER_H
#define __RFW_SOFTWARE_LOGWRITER_H

#include <stddef.h>
#include <stdarg.h>
#include <memory>

#include <pico/stdlib.h>
#include <pico/platform.h>
#include <pico/runtime.h>

#include <rfw/io/FileSystem.h>
#include <rfw/io/WriteStream.h>
#include <rfw/clock/AbsoluteClock.h>

#include <ff.h>

class LogWriter : public virtual RFW::WriteStream
{
public:
	LogWriter();

	FRESULT open(const char *path, uint8_t mode);
	FRESULT close();
	FRESULT flush();
	FRESULT error() const;

	size_t io_write(const char *data, size_t size) override;
	size_t __printflike(2, 3) io_writef(const char *format, ...) override;
	size_t io_flush() override;

	bool is_open() const;

	virtual ~LogWriter();

	void update() override;

private:
	FIL *_file;
	FRESULT _error;

	std::shared_ptr<RFW::AbsoluteClock> _clock;
	std::shared_ptr<RFW::FileSystem> _filesystem;

	size_t vwritef(const char *format, va_list args);
};

#endif // __RFW_SOFTWARE_LOGWRITER_H