#include "Global_config.h"

void setup(){
  Serial.begin(9600);
  wifi_init();
  server_init(); 
  TaskTempHumid_init();
  mqtt_init();
}

void loop(){
  // Nothing to do here, FreeRTOS tasks handle the work
}