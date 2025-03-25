#include "Global_config.h"

void setup(){
  Serial.begin(115200);
  wifi_init();
  server_init(); 
  mqtt_init();
  TaskSensor_init(); // All sensors included in 1 Task
  GPS_init();
}

void loop(){
  ElegantOTA.loop();
  if (ss.available() > 0){
    gps.encode(ss.read());
  }
}