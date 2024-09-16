/*
    This example code implements a "Power" Sensor Module. The PowerModule class
    is not based on any specific sensor and therefore can be used as a dummy sensor
    to test the surrounding hardware of the Sensor Module, such as the LCD and Wi-Fi
    support, by implementing a simple "sensor" that reads from an analogue input pin.
*/

#include <power_module.h>

#define POWER_AIN A0

// Initalise the power sensor data collection instance
PowerModule power(POWER_AIN);

void setup()
{
}

void loop()
{
  power.read();
  power.displayValues();
  if (WiFi.status() != WL_CONNECTED)
  {
    power.connectNetwork();
  }
  power.uploadData();
  delay(1000);
}
