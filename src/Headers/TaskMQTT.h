#ifndef TASKMQTT_H
#define TASKMQTT_H

#include "../include/Global_config.h"

extern PubSubClient client;

void mqtt_init();
void reconnect();
void publishData(String feed, String data);

#endif /* TASKMQTT_H */