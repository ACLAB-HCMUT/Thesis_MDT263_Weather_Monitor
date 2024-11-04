#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

// Import required libraries
#include "ESPAsyncWebServer.h"
#include "freertos/FreeRTOS.h"
#include "HardwareSerial.h"
#include "freertos/task.h"
#include "Adafruit_MQTT.h"
#include <PubSubClient.h>
#include <Arduino.h>
#include "SPIFFS.h"
#include <Wire.h>
#include "WiFi.h"

// Import project configuration
#include "../project_config.h"

// Import  Headers
#include "../src/Headers/ServerTask.h"
#include "../src/Headers/TaskMQTT.h"
#include "../src/Headers/TaskTempHumid.h"
#include "../src/Headers/WifiTask.h"

#endif //GLOBAL_CONFIG_H

