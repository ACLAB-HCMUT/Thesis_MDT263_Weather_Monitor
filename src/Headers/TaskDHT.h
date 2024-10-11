#ifndef TASKDHT_H
#define TASKDHT_H

#include <../include/Global_config.h>

extern uint8_t sensorRead[];
void TaskDHT_init();
extern float temperature;
extern float humidity;

#endif // TASKDHT_H