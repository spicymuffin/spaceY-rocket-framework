#ifndef HARDWARECONTROLLER_SERVOTYPE0_H
#define HARDWARECONTROLLER_SERVOTYPE0_H

#include "base_class/HardwareController.h"

#include "sensor/Accelerometer.h"
#include "sensor/Gyroscope.h"
#include "sensor/AngularAccelerometer.h"

class HardwareController_servotype0 : public HardwareController
{
public:
    HardwareController_servotype0(char* _hardwaremodelName);
    float getThermometerReading();
    float getAltimeterReading();
    AccelerometerDataPack getAccelerometerReading();

private:
protected:
};

#endif