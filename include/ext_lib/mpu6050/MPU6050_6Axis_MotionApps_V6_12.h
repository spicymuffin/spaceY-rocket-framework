// I2Cdev library collection
// Raspberry Pi Pico port for: MPU6050 I2C device class, 6-axis MotionApps 6.12 implementation
// Based on InvenSense MPU-6050 register map document rev. 2.0, 5/19/2011 (RM-MPU-6000A-00)
// 5/20/2013 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
// 2021-09-29 - Initial port release by Gino Ipóliti.
// 2019/7/10 - I incorporated DMP Firmware Version 6.12 Latest as of today with many features and bug fixes.
//           - MPU6050 Registers have not changed just the DMP Image so that full backwards compatibility is present
//           - Run-time calibration routine is enabled which calibrates after no motion state is detected
//           - once no motion state is detected Calibration completes within 0.5 seconds
//           - The Drawback is that the firmware image is larger.
//     ... - ongoing debug release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef _MPU6050_6AXIS_MOTIONAPPS20_H_
#define _MPU6050_6AXIS_MOTIONAPPS20_H_

#include "ext_lib/i2c/I2Cdev.h"
#include "ext_lib/math3d/math3d.h"
#include "pico/double.h"

const double PI = 3.1415926535897932384626433832795;

// MotionApps 2.0 DMP implementation, built using the MPU-6050EVB evaluation board
#define MPU6050_INCLUDE_DMP_MOTIONAPPS20 // same definitions Should work with V6.12


#endif /* _MPU6050_6AXIS_MOTIONAPPS20_H_ */