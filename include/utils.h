#ifndef __UTILS_H
#define __UTILS_H

#include <pico/stdlib.h>

void __printflike(1, 0) tud_cdc_printf(const char* fmt, ...);

void calculate_crc16(const uint8_t* data, size_t len, uint16_t* crc);

uint16_t assemble_uint16(uint8_t high, uint8_t low);

#endif // __UTILS_H