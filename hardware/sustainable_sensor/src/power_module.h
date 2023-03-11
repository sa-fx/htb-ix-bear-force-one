#include <sensor_module.h>

/*  This class can be used as a template for ease of implementing
    other sensors, or as a means of testing module hardware with
    a simple "read" function for a dummy sensor.
*/
class PowerModule : public SensorModule
{
public:
    PowerModule(int input_pin);
    ~PowerModule();
    void read();

private:
    const int POWER_TOO_HIGH = 400;
    const int POWER_VERY_HIGH = 300;
    const int POWER_HIGH = 200;
    const int POWER_OKAY = 100;
    const int POWER_EXCELLENT = 0;

    const int INPUT_PIN;
};