#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

// MPU6050 I2C address
#define MPU6050_ADDR 0x68

// MPU6050 Registers
#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

void mpu6050_init(i2c_inst_t* i2c)
{
    // Wake up the MPU6050
    uint8_t buf[2];
    buf[0] = PWR_MGMT_1;
    buf[1] = 0x00;  // Set to zero to wake up the MPU6050
    i2c_write_blocking(i2c, MPU6050_ADDR, buf, 2, false);
}

uint8_t mpu6050_read_who_am_i(i2c_inst_t* i2c)
{
    uint8_t reg = WHO_AM_I_REG;
    uint8_t data;
    i2c_write_blocking(i2c, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c, MPU6050_ADDR, &data, 1, false);
    return data;
}

void mpu6050_read_accel_gyro(i2c_inst_t* i2c, int16_t* buffer)
{
    uint8_t reg = ACCEL_XOUT_H;
    uint8_t data[14]; // To read all 6 accelerometers and gyro registers at once

    i2c_write_blocking(i2c, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c, MPU6050_ADDR, data, 14, false);

    // Convert high and low bytes to a 16-bit value for each axis
    for (int i = 0; i < 7; i++)
    {
        buffer[i] = (data[i * 2] << 8) | data[i * 2 + 1];
    }
}

int main()
{
    stdio_init_all();
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    mpu6050_init(i2c0);

    while (true)
    {
        uint8_t who_am_i = mpu6050_read_who_am_i(i2c0);
        printf("WHO_AM_I: %x\n", who_am_i);

        int16_t ag_data[7];
        mpu6050_read_accel_gyro(i2c0, ag_data);
        printf("Accel X: %d, Y: %d, Z: %d, Gyro X: %d, Y: %d, Z: %d\n",
            ag_data[0], ag_data[1], ag_data[2], ag_data[3], ag_data[4], ag_data[5]);

        sleep_ms(1000);
    }

    return 0;
}
