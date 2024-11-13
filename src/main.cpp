#include "Global_config.h"

void setup(){
  Serial.begin(115200);
  wifi_init();
  server_init(); 
  mqtt_init();
  //TaskTempHumid_init(); // All sensors included in 1 Task
  TaskSensor_init();
}

void loop(){
  // Nothing to do here, FreeRTOS tasks handle the work
}