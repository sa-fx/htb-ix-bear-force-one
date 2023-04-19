#ifndef sensor_module_h
#define sensor_module_h

#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <network_info.h>

#define WARNING_BUZZER 5
#define SD_PIN 10
#define LOGS_FILE "logs.txt"
#define RESULTS_FILE "results.txt"
#define CONFIG_FILE "config.txt"

// Text for printing to the LCD Display
const String SENSOR_STATUS[5] = {"Dangerous", "Bad", "Satisfactory", "Good", "Excellent"};
const String NETWORK_STATES[7] = {"Idle", "SSID Not Found", "Scan Complete", "Connected", "Failed", "Lost", "Disconnected"};

// Network objects
static WiFiClient client_;
static IPAddress local_ip_;
// static HttpClient http_;

// Set display address, and display dimensions
static LiquidCrystal_I2C display_(0x27, 20, 4);

static File sd_file_;

class SensorModule
{
public:
  SensorModule();

  /**
   * @brief Read data from sensor - Implementation dependent
   *        on sensor in question
   */
  virtual void read() = 0;

  void setSensorType(String sensor);
  void setDisplayName(String name);
  void setValueLimits(int too_high, int very_high, int high, int okay, int excellent);

  /**
   * @brief   Open the SD card and start writting to a file
   * @param   file_name The file to be accessed
   * @returns The file to be accessed as a File object
   */
  File startSD(String file_name);

  /**
   * @brief (Re)Connect to the network specified under
   *        network_info.h
   */
  void connectNetwork();

  /**
   * @brief Read the location info from the SD card and
   *        assign to the appropriate variables
   */
  void getLocationInfo();

  /**
   * @brief Read from the SD card if the module should run
   *        in debug mode
   */
  void configureDebug();

  void setValue(int value);

  /**
   * @brief   Use safety levels (pre-defined) to determine if
   *          sensor measurement is safe, unsafe, or dangerous
   * @return  Value referring to safety level (0-4)
   */
  int processData();

  /**
   * @brief Print module info to the LCD display
   */
  void displayValues();

  /**
   * @brief Send module data to the data server
   *        via HTTP/POST
   */
  void uploadData();

protected:
  String sensor_type_;
  String display_name_;
  String campus_;
  String building_;
  String room_;
  int sensor_value_;
  bool debug_flag_;
  int value_too_high;
  int value_very_high;
  int value_high;
  int value_okay;
  int value_excellent;
};

#endif