#include "co2_module.h"

CO2Module::CO2Module(int input_pin)
{
    setSensorType("CO2");
    setDisplayName("CO2 (ppm): ");
    CO2Sensor co2(input_pin, CO2_INERTIAL_COEFF, CO2_NUM_OF_READINGS);
    setValueLimits(CO2_TOO_HIGH, CO2_VERY_HIGH, CO2_HIGH, CO2_OKAY, CO2_EXCELLENT);
    pinMode(input_pin, INPUT);
}

CO2Module::~CO2Module(){};

void CO2Module::read()
{
    // TODOLater: Replace this hardcoded 0 with a read like what's commented out below (doesn't currently compile)
    //  int val = co2.read();
    int val = 0;
    setValue(val);
    return;
}