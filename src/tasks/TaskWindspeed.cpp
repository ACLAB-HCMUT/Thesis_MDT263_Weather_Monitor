#include "../src/Headers/TaskModbus485.h"

HardwareSerial RS485Serial(1);
float windspeed = 0.0;
uint8_t WindRequest[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};

//////////////////////////////////////////////////////////////////////////////////
void ClearResponseBuffer()
{
    size_t bytesToRead = RS485Serial.available();
    if (bytesToRead > 0)
    {
        byte out[bytesToRead];
        RS485Serial.readBytes(out, bytesToRead);
    }
}

void read_from_sensor(int ResponseSize)
{
    byte response[ResponseSize];

    int avail = RS485Serial.available();
    if (avail > 0)
    {
        size_t bytesRead = RS485Serial.readBytes(response, sizeof(response));

        Serial.println("");
        if (response[1] == 0x03)
        {
            windspeed = (response[3] << 8) | response[4];
            windspeed = windspeed / 10;
            Serial.print("Windspeed: " + String(windspeed) + " m/s");
            publishData("windspeed", String(windspeed));
        }
    }
    else
    {
        Serial.println("wire is loose on ES-WS-02");
    }
    memset(response, 0, sizeof(response));
}

void write_to_sensor()
{
    ClearResponseBuffer();
    RS485Serial.write(WindRequest, sizeof(WindRequest));
}

void modbus485_sensor_read(void *pvParameters)
{
    while (true)
    {
        write_to_sensor();
        vTaskDelay(delay_relay/portTICK_PERIOD_MS);
        read_from_sensor(16);
        vTaskDelay(3000/portTICK_PERIOD_MS);
    }
}

void TaskWindSpeed_init() {
    RS485Serial.begin(4800, SERIAL_8N1, D4, D3);
    xTaskCreate(modbus485_sensor_read, "Sensor-read", 4096, NULL, 1, NULL);
}