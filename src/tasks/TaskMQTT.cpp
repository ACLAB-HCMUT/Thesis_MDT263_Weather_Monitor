#include "../src/Headers/TaskMQTT.h"

WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

void TaskMQTT(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }

    while (!tb.connected())
    {
        Serial.println("Connecting to ThingsBoard MQTT...");
        if (!tb.connect(MQTT_SERVER, ACCESS_TOKEN, MQTT_PORT))
        {
            Serial.println("Failed to connect, retrying in 5 seconds");
            vTaskDelay(delay_temp / portTICK_PERIOD_MS);
            continue;
        }
        Serial.println("ThingsBoard MQTT Connected");
        tb.sendTelemetryData("IP", WiFi.localIP().toString().c_str());
    }

    while (true)
    {
        tb.loop();
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }
}

void mqtt_init()
{
    xTaskCreate(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
}
