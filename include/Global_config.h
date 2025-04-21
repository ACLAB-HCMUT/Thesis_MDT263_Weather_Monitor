#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

// Import required libraries
#include "ESPAsyncWebServer.h"
#include "freertos/FreeRTOS.h"
#include "HardwareSerial.h"
#include "freertos/task.h"
#include <Arduino.h>
#include "SPIFFS.h"
#include <Wire.h>
#include "WiFi.h"
#include <unistd.h>
#include <LittleFS.h>
#include <ElegantOTA.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Update.h>
#include <Arduino_MQTT_Client.h>
#include <ArduinoJson.h>
#include <ThingsBoard.h>

// Import project configuration
#include "../project_config.h"

// Import  Headers
#include "../src/Headers/ServerTask.h"
#include "../src/Headers/TaskMQTT.h"
#include "../src/Headers/TaskModbus485.h"
#include "../src/Headers/WifiTask.h"
#include "../src/Headers/TaskGPS.h"

// Define Delay value and GPIO
#define delay_sensor 2000
#define delay_temp 2000
#define delay_connect 100
#define delay_wifi 1000
#define delay_GPS 180000 // 3 minutes

#define D3 6
#define D4 7

#define D5 8
#define D6 9

#define D7 10
#define D8 17

#define D9 18
#define D10 21

#define SDA_PIN 11
#define SCL_PIN 12

#endif //GLOBAL_CONFIG_H