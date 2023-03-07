#include <sensor_module.h>
#include <CO2Sensor.h>

// TODOLater: Implement class
class CO2Sensor : public SensorModule
{
public:
    CO2Sensor();
    ~CO2Sensor();

private:
    const float CO2_INERTIAL_COEFF = 0.99;
    const int CO2_NUM_OF_READINGS = 100;
}