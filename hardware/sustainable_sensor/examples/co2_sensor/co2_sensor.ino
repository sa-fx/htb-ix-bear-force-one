#include <co2_sensor.h>

#define CO2_AIN A0

// Define CO2 ppm values
#define CO2_TOO_HIGH 3500
#define CO2_VERY_HIGH 2000
#define CO2_HIGH 1000
#define CO2_OKAY 800
#define CO2_EXCELLENT 400

// Initalise the CO2 sensor and its data collection instance
SensorModule co2("CO2", "CO2 (ppm): ");
CO2Sensor co2Sensor(CO2_AIN, CO2_INERTIAL_COEFF, CO2_NUM_OF_READINGS);

void setup()
{
  pinMode(CO2_AIN, INPUT);
}

void loop()
{
  int val = co2Sensor.read();
  int i;
  co2.setValue(val);
  if (val >= CO2_TOO_HIGH)
  {
    i = 0;
    digitalWrite(WARNING_BUZZER, HIGH);
    delay(250);
    digitalWrite(WARNING_BUZZER, LOW);
  }
  else if (val >= CO2_VERY_HIGH)
  {
    i = 1;
  }
  else if (val >= CO2_HIGH)
  {
    i = 2;
  }
  else if (val >= CO2_OKAY)
  {
    i = 3;
  }
  else
  {
    i = 4;
  }
  co2.displayValues(sensor_status[i]);
  if (WiFi.status() != WL_CONNECTED)
  {
    co2.connectNetwork();
  }
  co2.processData();
  delay(1000);
}
