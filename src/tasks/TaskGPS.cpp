#include "../src/Headers/TaskGPS.h"

TinyGPSPlus gps;
SoftwareSerial ss(D3, D4); //RXD_GPS = D4 , TXD_GPS = D3

double X = 0;
double Y = 0;

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
        if (WiFi.status() == WL_CONNECTED && tb.connected() && X != 0 && Y != 0)
        {
            String locationStr = String(X, 7) + "," + String(Y, 7);
            Serial.print("Location: ");
            Serial.println(locationStr);

            tb.sendTelemetryData("lat", X);
            tb.sendTelemetryData("long", Y);
            vTaskDelay(delay_GPS / portTICK_PERIOD_MS);
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS);
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
