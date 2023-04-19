#include <sustainable_sensors.h>

#define CO2_AIN A0

// Initalise the CO2 Sensor
CO2Module co2(CO2_AIN);

void setup()
{
}

void loop()
{
  co2.read();
  co2.displayValues();
  if (WiFi.status() != WL_CONNECTED)
  {
    co2.connectNetwork();
  }
  co2.uploadData();
  delay(1000);
}
