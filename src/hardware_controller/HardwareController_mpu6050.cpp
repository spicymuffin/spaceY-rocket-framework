// implementing
#include "hardware_controller/HardwareController_mpu6050.h"

// param
#include "param.h"
#include "debug_param.h"

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

// util
#include "util/CircularBuffer.h"

void HardwareController_mpu6050::init()
{
}

void HardwareController_mpu6050::init_dmp()
{
}

HardwareController_mpu6050::HardwareController_mpu6050(
    const char *_hardware_name,
    int _update_frequency,
    i2c_inst_t *_i2c_inst,
    uint _baudrate,
    CircularBuffer<VectorInt16> *_accelerometer_data_receivers[],
    CircularBuffer<VectorInt16> *_gyroscope_data_receivers[],
    CircularBuffer<Quaternion> *_orientation_data_receivers[],
    uint8_t _norientation_data_receivers,
    uint8_t _naccelerometer_data_receivers,
    uint8_t _ngyroscope_data_receivers)

    :

      HardwareController(_hardware_name, _update_frequency)
{
    int device_status = -1;

#if DBGMSG_HC_MPU6050
    printf("[STATUS]:[HC_MPU6050] starting intialization sequence\n");
#endif

    /// TODO: sets to default without regard to input. fix it.

    // set internal variables
    i2c_inst = i2c_default;
    baudrate = _baudrate;

    interrupt_status = 0;

    orientation_data_receivers_ref = _orientation_data_receivers;
    accelerometer_data_receivers_ref = _accelerometer_data_receivers;
    gyroscope_data_receivers_ref = _gyroscope_data_receivers;

    norientation_data_receivers = _norientation_data_receivers;
    naccelerometer_data_receivers = _naccelerometer_data_receivers;
    ngyroscope_data_receivers = _ngyroscope_data_receivers;

#if DBGMSG_HC_MPU6050
    printf("[  OK  ]:[HC_MPU6050] reference copying completed\n");
#endif

    // initialize i2c and hardware
    i2c_init(i2c_inst, baudrate);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

#if DBGMSG_HC_MPU6050
    printf("[  OK  ]:[HC_MPU6050] gpio and i2c init completed\n");
#endif

    // initialize the mpu (basic switch on)
    mpu.initialize();

#if DBGMSG_HC_MPU6050
    printf("[  OK  ]:[HC_MPU6050] mpu basic init sequence completed\n");
#endif

    // initialize the mpu's dmp processor, load its firmware
    device_status = mpu.dmpInitialize();

#if DBGMSG_HC_MPU6050
    printf("[  OK  ]:[HC_MPU6050] mpu dmp init sequence completed\n");
#endif

    // calibrate the sensors
    mpu.CalibrateAccel(10);
    mpu.CalibrateGyro(10);

#if DBGMSG_HC_MPU6050
    printf("[  OK  ]:[HC_MPU6050] hardware calibration sequence completed\n");
#endif

    if (device_status == 0)
    {
        // turn on the dmp processor
        mpu.setDMPEnabled(true);
        fifo_packet_size = mpu.dmpGetFIFOPacketSize();
#if DBGMSG_HC_MPU6050
        printf("[  OK  ]:[HC_MPU6050] fifo packet size attained. size=%u\n", fifo_packet_size);
#endif
    }
    else
    {
#if DBGMSG_HC_MPU6050
        printf("[ FAIL ]:[HC_MPU6050] device status=%d, fifo packet size unattainable\n", device_status);
#endif
    }
}

const int HardwareController_mpu6050::update()
{
    if (!dmp_ready)
    {
        return 1; // dmp data isnt ready
    }

    fifo_count = mpu.getFIFOCount();
    if ((interrupt_status & 0x10) || fifo_count == 1024)
    {
#if DBGMSG_HC_MPU6050
        printf("[ WARN ]:[HC_MPU6050] fifo overflow, fifo_count=%u\n", fifo_count);
#endif
        mpu.resetFIFO();
    }
    else // if (interrupt_status & 0x01) // bro help i need interrupts
    {
        while (fifo_count < fifo_packet_size)
        {
            fifo_count = mpu.getFIFOCount();
        }

        mpu.getFIFOBytes(fifo_buffer, fifo_packet_size);
        fifo_count -= fifo_packet_size;

        // get the orientation data in the dmp packet
        mpu.dmpGetQuaternion(&ornt, fifo_buffer);
        for (uint8_t i = 0; i < norientation_data_receivers; i++)
        {
            // write the data to each subscriber
            orientation_data_receivers_ref[i]->buffer_write(&ornt);
        }

        // get the acceleration data in the dmp packet
        mpu.dmpGetAccel(&accl, fifo_buffer);
        for (uint8_t i = 0; i < naccelerometer_data_receivers; i++)
        {
            // write the data to each subscriber
            accelerometer_data_receivers_ref[i]->buffer_write(&accl);
        }

        // get the gyroscope data in the dmp packet
        mpu.dmpGetGyro(&accl, fifo_buffer);
        for (uint8_t i = 0; i < ngyroscope_data_receivers; i++)
        {
            // write the data to each subscriber
            gyroscope_data_receivers_ref[i]->buffer_write(&gyro);
        }
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