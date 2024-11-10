#include "Global_config.h"

void setup(){
  Serial.begin(115200);
  wifi_init();
  server_init(); 
  mqtt_init();
  TaskWindSpeed_init();
}

void loop(){
  // Nothing to do here, FreeRTOS tasks handle the work
}