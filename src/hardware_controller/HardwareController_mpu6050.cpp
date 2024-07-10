// implementing
#include "hardware_controller/HardwareController_mpu6050.h"

#include "param.h"

// base_class
#include "base_class/HardwareController.h"

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "hardware/dma.h" // rewrite with dma use?

// dependcies
#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"

#include "ext_lib/mpu6050/MPU6050_6Axis_MotionApps_V6_12.h"
#include "ext_lib/mpu6050/MPU6050.h"

void HardwareController_mpu6050::init()
{

}

void HardwareController_mpu6050::init_dmp()
{

}

HardwareController_mpu6050::HardwareController_mpu6050(const char* _hardwareName, i2c_inst_t* _i2c_inst, uint _baudrate)
    : HardwareController(_hardwareName)
{
    int device_status = -1;

    /// TODO: sets to default without regard to input. fix it.

    // set internal variables
    i2c_inst = i2c_default;
    baudrate = _baudrate;

    // initialize i2c and hardware
    i2c_init(i2c_inst, baudrate);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // initialize the mpu (basic switch on)
    mpu.initialize();

    // initialize the mpu's dmp processor, load its firmware
    device_status = mpu.dmpInitialize();

    // calibrate the sensors
    mpu.CalibrateAccel(10);
    mpu.CalibrateGyro(10);

    if (device_status == 0)
    {
        // turn on the dmp processor
        mpu.setDMPEnabled(true);
        fifo_packet_size = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        printf("mpu6050 init sequence fatal error: failed to initialize the dmp\n");
    }
}

const int HardwareController_mpu6050::update()
{
    if (!dmp_ready)
    {
        return 1; // dmp data isnt ready
    }

    fifo_count = mpu.getFIFOCount();
    if (fifo_count == (uint16_t)(-1))
    {
        printf("mpu6050 timeout get fifocount timeout error\n");
        mpu.resetFIFO();
    }
    if ((interrupt_status & 0x01) || fifo_count == 1024)
    {
        printf("mpu6050 FIFO overflow\n");
        mpu.resetFIFO();
    }
    else if (interrupt_status & 0x01)
    {
        while (fifo_count < fifo_packet_size)
        {
            fifo_count = mpu.getFIFOCount();
            if (fifo_count == (uint16_t)(-1))
            {
                printf("mpu6050 timeout get fifocount timeout error\n");
                mpu.resetFIFO();
            }
        }

        mpu.getFIFOBytes(fifo_buffer, fifo_packet_size);
        fifo_count -= fifo_packet_size;
    }
    return 0;
}

const VectorInt16 HardwareController_mpu6050::get_accelerometer_reading()
{
    printf("-----------------> accelerometer reading\n");
    return {};
}

const VectorInt16 HardwareController_mpu6050::get_gyroscope_reading()
{
    printf("-----------------> gyroscope reading\n");
    return {};
}