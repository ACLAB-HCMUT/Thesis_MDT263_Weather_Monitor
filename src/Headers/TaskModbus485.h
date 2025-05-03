#ifndef TASKMODBUS485_H
#define TASKMODBUS485_H

#include <../include/Global_config.h>

extern float temperature;
extern float humidity;
extern float windspeed;
extern float windDirection;
extern float rainfallLevel;
extern float ultrasonicLevel;

void TaskSensor_init();

#endif // TASKMODBUS485_H