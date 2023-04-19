#include "sensor_module.h"

SensorModule::SensorModule()
{
  // Connect to local network
  connectNetwork();

  getLocationInfo();
  configureDebug();

  display_.init();
  display_.backlight();

  display_.setCursor(0, 0);
  display_.print("Sustainability Meter");
  display_.setCursor(0, 2);
  display_.print("Status: ");
  display_.setCursor(0, 3);
  display_.print("Net: ");
};

void SensorModule::setSensorType(String sensor)
{
  sensor_type_ = sensor;
  return;
}

void SensorModule::setDisplayName(String name)
{
  display_name_ = name;
  return;
}

void SensorModule::setValueLimits(int too_high, int very_high, int high, int okay, int excellent)
{
  value_very_high = too_high;
  value_very_high = very_high;
  value_high = high;
  value_okay = okay;
  value_excellent = excellent;
  return;
}

File SensorModule::startSD(String file_name)
{
  File file;
  if (SD.begin(SD_PIN))
  {
    file = SD.open(file_name, FILE_WRITE);
    file.print(millis());
    file.print(": ");
  }
  return file;
}

void SensorModule::connectNetwork()
{
  int network_state = WiFi.begin(SSID, PASSWORD);
  if (debug_flag_)
  {
    if (network_state == WL_CONNECTED)
    {
      local_ip_ = WiFi.localIP();
      Serial.print("Network connection established! Address: ");
      Serial.println(local_ip_);
    }
    else
    {
      Serial.print("Network connection failed. Code: ");
      Serial.println(NETWORK_STATES[network_state]);
    }
    sd_file_ = startSD(LOGS_FILE);
    if (sd_file_)
    {
      if (network_state == WL_CONNECTED)
      {
        sd_file_.print("Network connection established! Address: ");
        sd_file_.println(local_ip_);
      }
      else
      {
        sd_file_.print("Network connection failed. Code: ");
        sd_file_.println(NETWORK_STATES[network_state]);
      }
      sd_file_.close();
    }
  }
  return;
}

// TODOLater: Implement function
void SensorModule::getLocationInfo()
{
  sd_file_ = startSD(CONFIG_FILE);
  if (sd_file_)
  {
    // Read from SD card file
    sd_file_.close();
  }
  else
  {
    campus_ = "NO_CAMPUS";
    building_ = "NO_BUILDING";
    room_ = "NO_ROOM";
  }
  return;
}

void SensorModule::configureDebug()
{
  sd_file_ = startSD(CONFIG_FILE);
  if (sd_file_)
  {
    // TODOLater: Replace this line with read debug from SD file
    debug_flag_ = false;
    sd_file_.close();
    if (debug_flag_)
    {
      Serial.begin(9600);
      Serial.println("Debug begin");
      sd_file_ = startSD(LOGS_FILE);
      if (sd_file_)
      {
        sd_file_.println("Debug begin.");
        sd_file_.close();
      }
    }
  }
  else
  {
    debug_flag_ = false;
  }
  return;
}

void SensorModule::setValue(int value)
{
  sensor_value_ = value;
  return;
}

int SensorModule::processData()
{
  int status;
  if (sensor_value_ >= value_too_high)
  {
    status = 0;
    digitalWrite(WARNING_BUZZER, HIGH);
    delay(250);
    digitalWrite(WARNING_BUZZER, LOW);
  }
  else if (sensor_value_ >= value_very_high)
  {
    status = 1;
  }
  else if (sensor_value_ >= value_high)
  {
    status = 2;
  }
  else if (sensor_value_ >= value_okay)
  {
    status = 3;
  }
  else
  {
    status = 4;
  }
  return status;
}

void SensorModule::displayValues()
{
  String message = SENSOR_STATUS[processData()];
  int network_state = WiFi.status();
  display_.setCursor(0, 1);
  display_.print(display_name_);
  display_.setCursor(11, 1);
  display_.print(sensor_value_);
  display_.setCursor(8, 2);
  display_.print(message);
  display_.setCursor(5, 3);
  display_.print(NETWORK_STATES[network_state]);

  if (debug_flag_)
  {
    Serial.print(display_name_);
    Serial.println(sensor_value_);
    Serial.print("Status: ");
    Serial.println(message);
    Serial.print("Current network state code: ");
    Serial.println(network_state);
    sd_file_ = startSD(LOGS_FILE);
    if (sd_file_ != NULL)
    {
      sd_file_.print("Current network state code: ");
      sd_file_.println(network_state);
      sd_file_.close();
    }
  }
  // Try to reconnect if not connected
  if (network_state != WL_CONNECTED)
  {
    connectNetwork();
  }
  return;
}

// TODOLater: Fix the network implementations for pushing data
void SensorModule::uploadData()
{
  // if (WiFi.status() == WL_CONNECTED && client_.connected())
  // {
  //   http_.begin(client_, DATA_SERVER);
  //   http_.addHeader("Content-Type", "application/json");
  //   String httpRequestData = "{\",\"key\":\"";
  //   httpRequestData += sensor_type_;
  //   httpRequestData += "\",\"campus\":\"";
  //   httpRequestData += campus_;
  //   httpRequestData += "\",\"location\":\"";
  //   httpRequestData += building_;
  //   httpRequestData += "-";
  //   httpRequestData += room_;
  //   httpRequestData += "\",\"data\":\"";
  //   httpRequestData += sensor_value_;
  //   httpRequestData == "\"}";
  //   int http_code = http_.POST(httpRequestData);
  //   if (debug_flag_)
  //   {
  //     Serial.println("HTTP POST Result: " + http_code);
  //   }
  //   http_.end();
  // }
  // else
  // {
  //   if (debug_flag_)
  //   {
  //     sd_file_ = startSD(LOGS_FILE);
  //     if (sd_file_ != NULL)
  //     {
  //       sd_file_.print("Post unsuccessful. Network Status: ");
  //       sd_file_.println(NETWORK_STATES[WiFi.status()]);
  //       sd_file_.close();
  //     }

  //     Serial.print("Post unsuccessful. Network Status: ");
  //     Serial.println(NETWORK_STATES[WiFi.status()]);
  //   }
  // }
  // sd_file_ = startSD(RESULTS_FILE);
  // if (sd_file_ != NULL)
  // {
  //   sd_file_.println(sensor_value_);
  //   sd_file_.close();
  // }
  return;
}
