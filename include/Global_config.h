#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT20.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MQTT.h"
#include "HardwareSerial.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

//import devices / Headers
#include "../project_config.h"
#include "../src/Headers/TaskMQTT.h"
#include "../src/Headers/TaskDHT.h"
#include "../src/Headers/WifiTask.h"
#include "../src/Headers/ServerTask.h"
#include "../src/Headers/TaskLCD.h"

#endif //GLOBAL_CONFIG_H

