#include "sustainable_sensor.h"

SensorModule::SensorModule(String sensor_type, String display_name, String campus, String building, String room)
{
  sensor_type_ = sensor_type;
  display_name_ = display_name;
  campus_ = campus;
  building_ = building;
  room_ = room;

  // Connect to local network
  int network_state = WiFi.begin(SSID, PASSWORD);

  display.init();
  display.backlight();

  display.setCursor(0, 0);
  display.print("Sustainability Meter");
  display.setCursor(0, 2);
  display.print("Status: ");
  display.setCursor(0, 3);
  display.print("Net: ");
};

void SensorModule::setValue(int value)
{
  sensor_value_ = value;
  return;
}

void SensorModule::displayValues(String message)
{
  display.setCursor(0, 1);
  display.print(display_name_);
  display.setCursor(11, 1);
  display.print(sensor_value_);
  display.setCursor(8, 2);
  display.print(message);
  return;
}

// TODOLater: Make this string concatenation better
void SensorModule::sendData()
{
  if (WiFi.status() == WL_CONNECTED && client.connected())
  {
    http.begin(client, DATA_SERVER);
    http.addHeader("Content-Type", "application/json");
    String httpRequestData = "{\",\"key\":\"";
    httpRequestData += sensor_type_;
    httpRequestData += "\",\"campus\":\"";
    httpRequestData += campus_;
    httpRequestData += "\",\"location\":\"";
    httpRequestData += building_;
    httpRequestData += "-";
    httpRequestData += room_;
    httpRequestData += "\",\"data\":\"";
    httpRequestData += sensor_value_;
    httpRequestData == "\"}";
    // int http_code = http.POST("{\"api_key\":\"" + API_KEY + "\",\"sensor\":\"" + sensor_type_ + "\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");
    int http_code = http.POST(httpRequestData);
    if (DEBUG_FLAG)
    {
      Serial.println("HTTP POST Result: " + http_code);
    }
    http.end();
  }
  return;
}

void SensorModule::displayNetworkStatus()
{
  int network_state = WiFi.status();
  if (DEBUG_FLAG)
  {
    Serial.print("Network error!");
    Serial.print("Current network state code: ");
    Serial.println(network_state);
  }
  display.setCursor(5, 3);
  if (network_state != WL_NO_SHIELD)
  {
    display.print(network_states[network_state]);
  }
  if (network_state != WL_CONNECTED)
  {
    WiFi.disconnect();
    network_state = WiFi.begin(SSID, PASSWORD);
  }
  return;
}
