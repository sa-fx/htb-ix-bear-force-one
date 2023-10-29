#include "sensor_module.h"

SensorModule::SensorModule()
{
  // Connect to local network
  connectNetwork();
  // Read config from SD file
  getLocationInfo();
  configureDebug();

  // Initialise LCD display
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
  if (debug_flag_)
  {
    Serial.println("Attempting to connect to SSID");
  }
  status = WiFi.begin(SSID, PASSWORD);
  // Wait 10 seconds to allow connection
  if (debug_flag_)
  {
    Serial.println(WiFi.status());
    sd.
  }
  return;
}

// TODOLater: Implement function
void SensorModule::getLocationInfo()
{
  sd_file_ = startSD(CONFIG_FILE);
  if (sd_file_)
  {
    // TODOLater: Read from SD card file
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
      writeDebugInfo("Debug begin.");
    }
  }
  else
  {
    debug_flag_ = false;
  }
  return;
}

void writeDebugInfo(String debug_message_)
{
  if (debug_flag_)
  {
    Serial.println((String)millis() + debug_message_);
    sd_file_ = startSD(LOGS_FILE);
    if (sd_file_)
    {
      sd_file_.println((String)millis() + debug_message_);
      sd_file_.close();
    }
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

  // Try to reconnect if not connected
  if (network_state != WL_CONNECTED)
  {
    connectNetwork();
  }
  return;
}

void SensorModule::uploadData()
{
  // Set up HTTP frame for sending
  String httpQueryData = "{\",\"key\":\"";
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
  // Close any open connections before sending a new request
  client_.stop();
  writeDebugInfo("Attempting to connect to server...");
  // From Arduino WiFi example code
  if (client_.connect(DATA_SERVER, SERVER_PORT))
  {
    client_.println("POST " + DATA_PATH + "HTTP/1.1");
    client_.println("Host: " + DATA_SERVER);
    client_.println("User-Agent: ArduinoWiFi/1.1");
    client_.println("Connection: close");
    client_.println();

    client_.println(httpQueryData);
  }
  // Report debug info
  if (debug_flag_)
  {
    // Report to SD file
    sd_file_ = startSD(LOGS_FILE);
    if (sd_file_ != NULL)
    {
      sd_file_.print("Post unsuccessful. Network Status: ");
      sd_file_.println(NETWORK_STATES[WiFi.status()]);
      sd_file_.close();
    }
    // Report to serial
    Serial.print("Post unsuccessful. Network Status: ");
    Serial.println(NETWORK_STATES[WiFi.status()]);
  }
  sd_file_ = startSD(RESULTS_FILE);
  if (sd_file_ != NULL)
  {
    sd_file_.println(sensor_value_);
    sd_file_.close();
  }
  return;
}
