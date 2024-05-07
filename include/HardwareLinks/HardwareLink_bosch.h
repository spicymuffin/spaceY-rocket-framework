#ifndef HARDWARELINK_BOSCH_H
#define HARDWARELINK_BOSCH_H

#include "HardwareLink.h"

#include "Accelerometer.h"
#include "Thermometer.h"
#include "Gyroscope.h"
#include "AngularAccelerometer.h"
#include "Altimeter.h"

#include <string>

class HardwareLink_bosch : public HardwareLink
{
public:
    HardwareLink_bosch(string _hardwareName);
    float getThermometerReading();
    float getAltimeterReading();
    AccelerometerDataPack getAccelerometerReading();

private:
protected:
};

#endif