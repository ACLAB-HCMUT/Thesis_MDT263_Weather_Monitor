#ifndef TASKTEMPHUMID_H
#define TASKTEMPHUMID_H

#include <../include/Global_config.h>

extern uint8_t sensorRead[];
void TaskTempHumid_init();
extern float temperature;
extern float humidity;

#endif // TASKTEMPHUMID_H