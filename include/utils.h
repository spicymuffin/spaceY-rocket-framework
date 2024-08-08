#ifndef __UTILS_H
#define __UTILS_H

#include <pico/stdlib.h>

void __printflike(1, 0) tud_cdc_printf(const char *fmt, ...);

#endif // __UTILS_H