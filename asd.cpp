#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// MPU6050 I2C address
#define MPU6050_ADDR   0x68

// MPU6050 Registers
#define PWR_MGMT_1     0x6B
#define TEMP_OUT_H     0x41
#define ACCEL_XOUT_H   0x3B
#define GYRO_XOUT_H    0x43

int16_t read_mpu6050_data(i2c_inst_t* i2c, uint8_t reg)
{
    uint8_t data[2];
    i2c_write_blocking(i2c, MPU6050_ADDR, &reg, 1, true); // Set register to read
    i2c_read_blocking(i2c, MPU6050_ADDR, data, 2, false); // Read 2 bytes
    return (int16_t)((data[0] << 8) | data[1]);
}

float read_temperature(i2c_inst_t* i2c)
{
    int16_t raw_temp = read_mpu6050_data(i2c, TEMP_OUT_H);
    return (raw_temp / 340.0) + 36.53;
}

int main()
{
    stdio_init_all();

    i2c_init(i2c0, 100 * 1000); // Initialize I2C0 at 100 kHz
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4); // Enable pull-up resistors
    gpio_pull_up(5);

    uint8_t buf[2] = { PWR_MGMT_1, 0x00 }; // Wake up the MPU6050
    i2c_write_blocking(i2c0, MPU6050_ADDR, buf, 2, false);

    while (1)
    {
        int32_t read_start_time = time_us_32();
        // Read accelerometer data
        int16_t ax = read_mpu6050_data(i2c0, ACCEL_XOUT_H);
        int16_t ay = read_mpu6050_data(i2c0, ACCEL_XOUT_H + 2);
        int16_t az = read_mpu6050_data(i2c0, ACCEL_XOUT_H + 4);

        // Read gyroscope data
        int16_t gx = read_mpu6050_data(i2c0, GYRO_XOUT_H);
        int16_t gy = read_mpu6050_data(i2c0, GYRO_XOUT_H + 2);
        int16_t gz = read_mpu6050_data(i2c0, GYRO_XOUT_H + 4);

        // Read temperature
        float temperature = read_temperature(i2c0);
        int32_t read_end_time = time_us_32();
        // Print all data
        printf("got data in: %zu\n", read_end_time - read_start_time);
        printf("Temp: %.2f C, Accel: (%d, %d, %d), Gyro: (%d, %d, %d)\n",
            temperature, ax, ay, az, gx, gy, gz);

        sleep_ms(100); // Delay for readability
    }

    return 0;
}