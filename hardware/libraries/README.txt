This code is designed for use with the following board:
- ESP32 WiFi enabled board

The following libraries are required to run this code for any sensor:
- Arduino_JSON/Arduino_JSON.h
- LiquidCrystal_I2C/LiquidCrystal_I2C.h
- SD.h
- SPI.h
- WiFi_Link/WiFi.h
- HTTPClient/HTTPClient.h
Note that LiquidCrystal_I2C.h may complain about being incompatible with the hardware architechture of the ESP32. This warning can be ignored.

The following libraries are required to run the code for a CO2 sensor:
- CO2Sensor-master/CO2Sensor.h

The following libraries are required to run the code for a VOC sensor:
- Adafruit SGP40 Sensor
- Adafruit BusIO
- Adafruit SHT31 Library
