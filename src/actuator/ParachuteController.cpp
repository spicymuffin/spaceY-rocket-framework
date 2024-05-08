#include "actuator/ParachuteController.h"

#include "param.h"

#include "sensor/Accelerometer.h"
#include "sensor/AngularAccelerometer.h"
#include "sensor/Gyroscope.h"

ParachuteController::ParachuteController(char *_name,
                                         int _updateFrequency,
                                         Accelerometer *_accelerometer,
                                         AngularAccelerometer *_angularAccelerometer,
                                         Gyroscope *_gyroscope) : RocketModule(_name, _updateFrequency)

{
    accelerometer_ref = _accelerometer;
    angularAccelerometer_ref = _angularAccelerometer;
    gyroscope_ref = _gyroscope;
}

void ParachuteController::deployParachute()
{
    // depoloy parachute
}

int ParachuteController::update()
{
    // if (parachute should be opened)
    // this->deployParachute();
    return 0;
}