#include "utils.h"

#include <stdlib.h>
#include <stdarg.h>

#include "tusb.h"

void tud_cdc_vprintf(const char *fmt, va_list args)
{
	size_t len = vsnprintf(NULL, 0, fmt, args) + 1;
	char *message = (char *)malloc(len);
	vsprintf(message, fmt, args);

	tud_cdc_write_str(message);
	tud_cdc_write_flush();
}

void __printflike(1, 0) tud_cdc_printf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	tud_cdc_vprintf(fmt, args);
	va_end(args);
}
