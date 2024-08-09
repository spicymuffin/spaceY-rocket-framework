#ifndef __UTILS_H
#define __UTILS_H

#include <pico/stdlib.h>

#ifndef NDEBUG
#define dprintf(writer, ...) RFW::io_writef(writer.get(), __VA_ARGS__)
#else
#define dprintf(writer, ...)
#endif

void __printflike(1, 0) tud_cdc_printf(const char *fmt, ...);

#endif // __UTILS_H