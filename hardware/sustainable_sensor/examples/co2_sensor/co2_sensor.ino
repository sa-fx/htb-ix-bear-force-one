#include <co2_module.h>
#include <network_info.h>
#include <power_module.h>
#include <sensor_module.h>
#include <tds_module.h>
#include <voc_module.h>

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
