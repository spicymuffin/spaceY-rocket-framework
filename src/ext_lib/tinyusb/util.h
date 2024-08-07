#ifndef __UTIL_H
#define __UTIL_H

#include <pico/stdlib.h>

#include <stddef.h>

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

#define CAT_2(X, Y) X##Y
#define CAT(X, Y) CAT_2(X, Y)

#define SERIAL_BUFFER_SIZE 2048

extern int32_t tud_cdc_buffer[SERIAL_BUFFER_SIZE];

#ifdef __cplusplus
extern "C"
{
#endif

	void __attribute__((noreturn)) __printflike(1, 0) tusb_panic(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

void __printflike(1, 0) tud_cdc_printf(const char *fmt, ...);

int8_t tud_cdc_buffer_get_int8(bool flush = true);
int16_t tud_cdc_buffer_get_int16(bool flush = true);
int32_t tud_cdc_buffer_get_int32(bool flush = true);
uint8_t tud_cdc_buffer_get_uint8(bool flush = true);
uint16_t tud_cdc_buffer_get_uint16(bool flush = true);
uint32_t tud_cdc_buffer_get_uint32(bool flush = true);

int8_t tud_cdc_buffer_get_fixed_int8(uint8_t length, bool flush = true);
int16_t tud_cdc_buffer_get_fixed_int16(uint8_t length, bool flush = true);
int32_t tud_cdc_buffer_get_fixed_int32(uint8_t length, bool flush = true);
uint8_t tud_cdc_buffer_get_fixed_uint8(uint8_t length, bool flush = true);
uint16_t tud_cdc_buffer_get_fixed_uint16(uint8_t length, bool flush = true);
uint32_t tud_cdc_buffer_get_fixed_uint32(uint8_t length, bool flush = true);

void tud_cdc_buffer_init();
void tud_cdc_buffer_flush();
int32_t tud_cdc_buffer_read();
void tud_cdc_buffer_write(int32_t c);

#endif // __UTIL_H