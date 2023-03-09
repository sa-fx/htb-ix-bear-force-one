#include <power_sensor.h>

#define POWER_AIN A0

// Define power values
#define POWER_TOO_HIGH 400
#define POWER_VERY_HIGH 300
#define POWER_HIGH 200
#define POWER_OKAY 100
#define POWER_EXCELLENT 0

// Initalise the power sensor data collection instance
SensorModule power("POWER", "Power (W): ");

void setup()
{
  pinMode(POWER_AIN, INPUT);
}

void loop()
{
  int power_reading = analogRead(POWER_AIN);
  int i;
  power.setValue(power_reading);
  if (power_reading >= POWER_TOO_HIGH)
  {
    i = 0;
    digitalWrite(WARNING_BUZZER, HIGH);
    delay(250);
    digitalWrite(WARNING_BUZZER, LOW);
  }
  else if (power_reading >= POWER_VERY_HIGH)
  {
    i = 1;
  }
  else if (power_reading >= POWER_HIGH)
  {
    i = 2;
  }
  else if (power_reading >= POWER_OKAY)
  {
    i = 3;
  }
  else
  {
    i = 4;
  }
  power.displayValues(sensor_status[i]);
  if (WiFi.status() != WL_CONNECTED)
  {
    power.connectNetwork();
  }
  power.processData();
  delay(1000);
}
