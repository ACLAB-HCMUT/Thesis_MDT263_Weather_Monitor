#include "../src/Headers/TaskDHT.h"

HardwareSerial RS485Serial(1);
uint8_t sensorRead[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};

float temperature = 0.0;
float humidity = 0.0;

void cleanBuffer()
{
    size_t bytesToRead = RS485Serial.available();
    if (bytesToRead > 0)
    {
        byte out[bytesToRead];
        RS485Serial.readBytes(out, bytesToRead);
    }
}

void read_from_sensor(int bufferSize)
{
    byte buffer[bufferSize];

    int avail = RS485Serial.available();
    if (avail > 0)
    {
        size_t bytesRead = RS485Serial.readBytes(buffer, sizeof(buffer));

        Serial.println("");
        if (buffer[1] == 0x03)
        {
            // Convert Temperature byte data to value
            temperature = (buffer[3] << 8) | buffer[4];
            temperature = temperature / 10;
            

            // Convert Humidity byte data to value
            humidity = (buffer[5] << 8) | buffer[6];
            humidity = humidity / 10;

            // Send converted data to Adafruit through MQTT function
            publishData("Temperature", String(temperature));
            publishData("Humidity", String(humidity));
        }
    }
    else
    {
        Serial.println("Failed to read data from sensor");
    }
    memset(buffer, 0, sizeof(buffer));
}

void write_to_sensor()
{
    cleanBuffer();
    int n = RS485Serial.write(sensorRead, sizeof(sensorRead));
}

void modbus485_sensor_read(void *pvParameters)
{
    while (true)
    {
        write_to_sensor(); // Turn Analog signal to Digital data
        vTaskDelay(delay_relay/portTICK_PERIOD_MS);
        read_from_sensor(BUFFER_SIZE); // Collect Digital data
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void TaskDHT_init()
{
    RS485Serial.begin(9600, SERIAL_8N1, RXD_RELAY, TXD_RELAY);
    xTaskCreate(modbus485_sensor_read, "READ_TEMP_HUMID", 4096, NULL, 1, NULL);
}
