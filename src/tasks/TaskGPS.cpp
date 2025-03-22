#include "../src/Headers/TaskGPS.h"

TinyGPSPlus gps;
SoftwareSerial ss(D3, D4); //RXD_GPS = D4 , TXD_GPS = D3

float X = 0;
float Y = 0;

void GPS_sensor()
{
    if (gps.location.isUpdated())
    {
        X = gps.location.lat();
        Y = gps.location.lng();
    }
}

void sendLocation(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected() && X != 0 && Y != 0)
        {
            String locationStr = String(X, 7) + "," + String(Y, 7);
            Serial.print("Location: ");
            Serial.println(locationStr);
            publishData("location", locationStr); 
            vTaskDelay(delay_GPS / portTICK_PERIOD_MS);
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS); // send location every 10 seconds
    }
}

void TaskGps(void *pvParameters)
{
    ss.begin(9600);
    while (true)
    {
        GPS_sensor();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void GPS_init()
{
    xTaskCreate(TaskGps, "TaskGPS", 4096, NULL, 1, NULL);
    xTaskCreate(sendLocation, "sendLocation", 4096, NULL, 2, NULL);
}
