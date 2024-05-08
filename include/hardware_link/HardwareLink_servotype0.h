#ifndef HARDWARELINK_SERVOTYPE0_H
#define HARDWARELINK_SERVOTYPE0_H

#include "base_class/HardwareLink.h"

#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

class HardwareLink_servotype0 : public HardwareLink
{
public:
    HardwareLink_servotype0(char* _hardwaremodelName);
    float getThermometerReading();
    float getAltimeterReading();
    AccelerometerDataPack getAccelerometerReading();

private:
protected:
};

#endif