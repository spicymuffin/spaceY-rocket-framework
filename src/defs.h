#ifndef __DEFS_H
#define __DEFS_H

#define PANIC_UART uart0

#define IMU_SPI_INST spi0
#define IMU_SPI_SCK 2
#define IMU_SPI_MOSI 3
#define IMU_SPI_MISO 4
#define IMU_SPI_CSn 5
#define IMU_RESET 10
#define IMU_SENSOR_TRIES 5

#define IMU_SENSOR_ID 0x7A
// #define IMU_SENSOR_ID2
#define IMU_FIRMWARE_H "Bosch_APP30_SHUTTLE_BHI260_BMP390-flash.fw.h"
#define IMU_FIRMWARE Bosch_APP30_SHUTTLE_BHI260_BMP390_flash_fw

// #define RTC_CONFIGURE_SUPPORT

#endif // __DEFS_H