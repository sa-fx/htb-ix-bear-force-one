#include <voc_sensor.h>

// Define VOC Index values
#define VOC_TOO_HIGH 400
#define VOC_VERY_HIGH 300
#define VOC_HIGH 200
#define VOC_OKAY 100
#define VOC_EXCELLENT 0

// Initalise the VOC sensor and its data collection instance
Adafruit_SGP40 sgp;
Adafruit_SHT31 sht31;
uint16_t sraw;
int32_t voc_index;
SensorModule voc("VOC", "VOC Index: ");

void setup()
{
}

void loop()
{
  float temperature = sht31.readTemperature();
  float humidity = sht31.readHumidity();
  voc_index = sgp.measureVocIndex(temperature, humidity);
  int i;
  voc.setValue(voc_index);
  if (voc_index >= VOC_TOO_HIGH)
  {
    i = 0;
    digitalWrite(WARNING_BUZZER, HIGH);
    delay(250);
    digitalWrite(WARNING_BUZZER, LOW);
  }
  else if (voc_index >= VOC_VERY_HIGH)
  {
    i = 1;
  }
  else if (voc_index >= VOC_HIGH)
  {
    i = 2;
  }
  else if (voc_index >= VOC_OKAY)
  {
    i = 3;
  }
  else
  {
    i = 4;
  }
  voc.displayValues(sensor_status[i]);
  if (WiFi.status() != WL_CONNECTED)
  {
    voc.connectNetwork();
  }
  voc.processData();
  delay(1000);
}
