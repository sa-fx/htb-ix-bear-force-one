#include <sensor_module.h>
#include <CO2Sensor.h>

class CO2Module : public SensorModule
{
public:
    CO2Module(int input_pin);
    ~CO2Module();
    void read();

private:
    const int CO2_TOO_HIGH = 3500;
    const int CO2_VERY_HIGH = 2000;
    const int CO2_HIGH = 1000;
    const int CO2_OKAY = 800;
    const int CO2_EXCELLENT = 400;

    const float CO2_INERTIAL_COEFF = 0.99;
    const int CO2_NUM_OF_READINGS = 100;
};