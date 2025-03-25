#include "../src/Headers/TaskModbus485.h"
// Only 1 Modbus RS485 for all sensors
// Sensor: ES-Integrate-ODR1 Temperature + Humidity
// Sensor: ES-WS-02 Wind Speed
// Sensor: ES-WS-04 Wind Direction
// Sensor: ES-RainF-01 Rainfall

// Sensor UART communication init
HardwareSerial RS485Serial(1);

// Wind Speed Sensor
float windspeed = 0.0;
uint8_t WindRequest[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};

// Temperature and Humidity Sensor
float temperature = 0.0;
float humidity = 0.0;
uint8_t TemperatureRequest[] = {0x04, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0x9F};
uint8_t HumidityRequest[] = {0x04, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x5F};

// Wind Direction Sensor
float windDirection = 0.0;
uint8_t WindDirectionRequest[] = {0x03, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD4, 0x28};

// Rainfall Sensor
float rainfallLevel = 0.0;
uint8_t RainfallRequest[] = {0x07, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x6C};

//Ultrasonic Sensor
//float ultrasonicLevel = 0.0;
//uint8_t LevelRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
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
        if (response[1] == 0x03) {
            float value = (response[3] << 8) | response[4];
            return value / divider;
        }
    }
    memset(response, 0, sizeof(response));
    return -1;
}

float ReadWindDirection(int responseSize) {
    byte response[responseSize];
    int available = RS485Serial.available();
    if (available >= responseSize) {
        RS485Serial.readBytes(response, responseSize);
        if (response[1] == 0x03) {
            float value = (response[3] << 8) | response[4];
            return value;
        }
    }
    memset(response, 0, sizeof(response));
    return -1;
}

void ReadWindSpeed() {
    SendCommand(WindRequest, sizeof(WindRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float ws = ReadFromSensor(7, 10.0);
    if (ws >= 0) {
        windspeed = ws;
        Serial.print("Windspeed: ");
        Serial.println(windspeed);
        tb.sendTelemetryData("windspeed", windspeed);
    } else {
        Serial.println("Failed to read windspeed from ES-WS-04");
    }
}

void ReadTemperature() {
    SendCommand(TemperatureRequest, sizeof(TemperatureRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float temp = ReadFromSensor(7, 10.0);
    if (temp >= 0) {
        temperature = temp;
        Serial.print("Temperature: ");
        Serial.println(temperature);
        tb.sendTelemetryData("temperature: ", temperature);
    } else {
        Serial.println("Failed to read temperature from ES-Integrate-ODR1-2ThongSo");
    }
}

void ReadHumidity() {
    SendCommand(HumidityRequest, sizeof(HumidityRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float hum = ReadFromSensor(7, 10.0);
    if (hum >= 0) {
        humidity = hum;
        Serial.print("Humidity: ");
        Serial.println(humidity);
        tb.sendTelemetryData("humidity", humidity);
    } else {
        Serial.println("Failed to read humidity from ES-Integrate-ODR1-2ThongSo");
    }
}

void ReadWindDirection() {
    SendCommand(WindDirectionRequest, sizeof(WindDirectionRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float wd = ReadWindDirection(7);
    if (wd >= 0) {
        windDirection = wd;
        Serial.print("Wind Direction: ");
        Serial.println(windDirection);
        tb.sendTelemetryData("windDirection", windDirection);
    } else {
        Serial.println("Failed to read wind direction from ES-WS-04");
    }
}

void ReadRainfall() {
    SendCommand(RainfallRequest, sizeof(RainfallRequest));
    vTaskDelay(100 / portTICK_PERIOD_MS);
    float rain = ReadFromSensor(7, 10.0);
    if (rain >= 0) {
        rainfallLevel = rain;
        Serial.print("Rainfall Level: ");
        Serial.println(rainfallLevel);
        tb.sendTelemetryData("rainfallLevel", rainfallLevel);
    } else {
        Serial.println("Failed to read rainfall level from ES-RainF-01");
    }

}
////Check Sensor raw data in case Insight Sensor app doesn't work
//void PrintHexArray(const byte *array, size_t size) {
//    Serial.print("Raw Response: ");
//    for (size_t i = 0; i < size; i++) {
//        if (array[i] < 0x10) {
//            Serial.print("0");
//        }
//        Serial.print(array[i], HEX);
//        Serial.print(" ");
//    }
//    Serial.println();
//}

//float ReadUltraSonicLevel(int responseSize) {
//    byte response[responseSize];
//    int available = RS485Serial.available();
//    if (available >= responseSize) {
//        RS485Serial.readBytes(response, responseSize);
//
//        // Print the raw response in hexadecimal format
//        //PrintHexArray(response, responseSize);
//
//        // Validate the response
//        if (response[0] == 0x01 && response[1] == 0x03 && response[2] == 0x04) {
//            uint32_t rawData =  (response[5] << 8) | response[6];
//            return rawData / 10.0;
//        }
//    }
//    memset(response, 0, sizeof(response));
//    return -1;
//}
//
//// Function to read the ultrasonic level
//void ReadUltrasonicSensor() {
//    SendCommand(LevelRequest, sizeof(LevelRequest));
//    vTaskDelay(100 / portTICK_PERIOD_MS);
//    float level = ReadUltraSonicLevel(9);
//    if (level >= 0) {
//        ultrasonicLevel = level;
//        Serial.print("Ultrasonic Level: ");
//        Serial.println(ultrasonicLevel);
//        publishData("ultrasonicLevel", String(ultrasonicLevel));
//    } else {
//        Serial.println("Failed to read data from ES-ULS-02");
//    }
//}
//

void SensorRead(void *pvParameters) {
    while (true) {
        ReadWindSpeed();
        //vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
        ReadTemperature();
        //vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
        ReadHumidity();
        //vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
        ReadWindDirection();
        //vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
        ReadRainfall();
        //vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
        //ReadUltrasonicSensor()
        vTaskDelay(delay_sensor / portTICK_PERIOD_MS);
    }
}

void TaskSensor_init() {
    RS485Serial.begin(9600, SERIAL_8N1, D5, D6); // RX = D5, TX = D6
    xTaskCreate(SensorRead, "SensorRead", 4096, NULL, 1, NULL);
}