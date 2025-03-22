#ifndef INC_TASKGPS_H_
#define INC_TASKGPS_H_

#include "../include/Global_config.h"

void GPS_init();

extern TinyGPSPlus gps;
extern SoftwareSerial ss;

#endif /* INC_TASKGPS_H_ */