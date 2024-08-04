#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include "param.h"
#include "debug_param.h"

// base_class

// system

// pico sdk
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// dependencies

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer();
    int buffer_write(T* _data);
    int buffer_write(T* _data, uint8_t n);
    int buffer_read(T* _data);
    int buffer_read(T* _data, uint8_t n);
    uint8_t get_new_cnt();

private:
    uint8_t nelem_written;
    uint8_t read_ptr;
    uint8_t write_ptr;
    T buffer[DR_BUFFER_LENGTH];
};

// implementation

template <typename T>
CircularBuffer<T>::CircularBuffer() : nelem_written(0), read_ptr(0) {}

template <typename T>
int CircularBuffer<T>::buffer_write(T* _data)
{
    buffer[write_ptr] = *_data;
    write_ptr = (write_ptr + 1) % DR_BUFFER_LENGTH;
    if (nelem_written < DR_BUFFER_LENGTH)
    {
        #if DBGMSG_CIRCULAR_BUFFER
        printf("[STATUS]:[CIRCBUF] writing data\n");
        #endif
        nelem_written++;
    }
    else
    {
        read_ptr = (read_ptr + 1) % DR_BUFFER_LENGTH;
    }

    return 0;
}

template <typename T>
int CircularBuffer<T>::buffer_write(T* _data, uint8_t n)
{
    for (uint8_t i = 0; i < n; ++i)
    {
        buffer[write_ptr] = _data[i];
        write_ptr = (write_ptr + 1) % DR_BUFFER_LENGTH;
        if (nelem_written < DR_BUFFER_LENGTH)
        {
            nelem_written++;
        }
        else
        {
            read_ptr = (read_ptr + 1) % DR_BUFFER_LENGTH;
        }
    }

    return 0;
}

template <typename T>
int CircularBuffer<T>::buffer_read(T* _data)
{
    if (nelem_written > 0)
    {
        #if DBGMSG_CIRCULAR_BUFFER
        printf("[STATUS]:[CIRCBUF] reading data\n");
        #endif
        *_data = buffer[read_ptr];
        read_ptr = (read_ptr + 1) % DR_BUFFER_LENGTH;
        nelem_written--;
        return 0;
    }
    else
    {
        return -1;
    }
}

template <typename T>
int CircularBuffer<T>::buffer_read(T* _data, uint8_t n)
{
    for (uint8_t i = 0; i < n; ++i)
    {
        if (nelem_written > 0)
        {
            _data[i] = buffer[read_ptr];
            read_ptr = (read_ptr + 1) % DR_BUFFER_LENGTH;
            nelem_written--;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

template <typename T>
uint8_t CircularBuffer<T>::get_new_cnt()
{
    return nelem_written;
}

#endif