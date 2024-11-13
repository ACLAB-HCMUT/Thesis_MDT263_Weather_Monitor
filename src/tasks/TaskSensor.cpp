#include "../src/Headers/TaskModbus485.h"
// Sensor: ES-WS-02 for Wind Speed and ES-Integrate-ODR1-2ThongSo for Temp/Humidity
HardwareSerial RS485Serial(1);

// Wind Speed Sensor
float windspeed = 0.0;
uint8_t WindRequest[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};

// Temperature and Humidity Sensor
float temperature = 0.0;
float humidity = 0.0;
uint8_t TemperatureRequest[] = {0x04, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0x9F};
uint8_t HumidityRequest[] = {0x04, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x5F};

//////////////////////////////////////////////////////////////////////////////////
// Clears the response buffer before sending a new request
void CleanResponseBuffer() {
    size_t bytesToRead = RS485Serial.available();
    if (bytesToRead > 0) {
        byte out[bytesToRead];
        RS485Serial.readBytes(out, bytesToRead);
    }
}

// Sends a command to the specified sensor
void SendCommand(uint8_t *request, size_t size) {
    CleanResponseBuffer();
    RS485Serial.write(request, size);
}

// Reads and parses data from the sensor
float ReadFromSensor(int responseSize, float divider) {
    byte response[responseSize];
    int available = RS485Serial.available();
    if (available >= responseSize) {
        RS485Serial.readBytes(response, responseSize);
        if (response[1] == 0x03) { // Check function code
            float value = (response[3] << 8) | response[4];
            return value / divider;
        }
    }
    memset(response, 0, sizeof(response)); // Clear response for multivalue sensors
    return -1;
}

void ReadWindSpeed() {
    SendCommand(WindRequest, sizeof(WindRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float ws = ReadFromSensor(7, 10.0);  // Wind speed is divided by 10
    if (ws >= 0) {
        windspeed = ws;
        Serial.print("Windspeed: ");
        Serial.println(windspeed);
        publishData("windspeed", String(windspeed));
    } else {
        Serial.println("Failed to read windspeed from ES-WS-04");
    }
}

void ReadTemperature() {
    SendCommand(TemperatureRequest, sizeof(TemperatureRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float temp = ReadFromSensor(7, 10.0);  // Temperature is divided by 10
    if (temp >= 0) {
        temperature = temp;
        Serial.print("Temperature: ");
        Serial.println(temperature);
        publishData("temperature", String(temperature));
    } else {
        Serial.println("Failed to read temperature from ES-Integrate-ODR1-2ThongSo");
    }
}

void ReadHumidity() {
    SendCommand(HumidityRequest, sizeof(HumidityRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float hum = ReadFromSensor(7, 10.0);  // Humidity is divided by 10
    if (hum >= 0) {
        humidity = hum;
        Serial.print("Humidity: ");
        Serial.println(humidity);
        publishData("humidity", String(humidity));
    } else {
        Serial.println("Failed to read humidity from ES-Integrate-ODR1-2ThongSo");
    }
}

void SensorRead(void *pvParameters) {
    while (true) {
        ReadWindSpeed();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        ReadTemperature();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        ReadHumidity();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void TaskSensor_init() {
    RS485Serial.begin(9600, SERIAL_8N1, D5, D6); // TX = D3, RX = D4
    xTaskCreate(SensorRead, "SensorRead", 4096, NULL, 1, NULL);
}
