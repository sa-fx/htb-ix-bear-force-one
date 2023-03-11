#include "Arduino.h"
#include "power_module.h"

PowerModule::PowerModule(int input_pin)
{
    INPUT_PIN = input_pin;
    pinMode(INPUT_PIN, INPUT);
    setSensorType("POWER");
    setDisplayName("Power (W): ");
    setValueLimits(POWER_TOO_HIGH, POWER_VERY_HIGH, POWER_HIGH, POWER_OKAY, POWER_EXCELLENT);
}

PowerModule::~PowerModule(){};

void PowerModule::read()
{
    sensor_value = analogRead(INPUT_PIN);
    return;
}