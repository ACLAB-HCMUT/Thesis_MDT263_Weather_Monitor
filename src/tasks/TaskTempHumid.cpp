// #include "../src/Headers/TaskModbus485.h"
// // Only 1 Modbus RS485  for all sensors
// // Sensor: ES-Integrate-ODR1 Temperature + Humidity
// // Sensor: ES-WS-02 Wind Speed
// HardwareSerial RS485Serial(1);
// float temperature = 0.0;
// float humidity = 0.0;
// float windspeed = 0;
// 
// uint8_t TemperatureRequest[] = {0x04, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0x9F};
// uint8_t HumidityRequest[] = {0x04, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x5F};
// 
// //////////////////////////////////////////////////////////////////////////////////
// void CleanTempHumidResponse()
// {
//     size_t bytesToRead = RS485Serial.available();
//     if (bytesToRead > 0)
//     {
//         byte out[bytesToRead];
//         RS485Serial.readBytes(out, bytesToRead);
//     }
// }
// 
// void SendCommand(uint8_t *request, size_t size)
// {
//     CleanTempHumidResponse();
//     RS485Serial.write(request, size);
// }
// 
// void ReadTempHumidSensor(uint8_t *request, float &value, const char* label)
// {
//     SendCommand(request, 8);
//     vTaskDelay(200 / portTICK_PERIOD_MS);
// 
//     byte response[7];
//     memset(response, 0, sizeof(response));
// 
//     if (RS485Serial.available() >= 7)
//     {
//         RS485Serial.readBytes(response, 7);
// 
//         if (response[1] == 0x03)
//         {
//             value = ((response[3] << 8) | response[4]) / 10.0;
//             Serial.print(label);
//             Serial.println(value);
//             publishData(label, String(value));
//         }
//         else
//         {
//             Serial.println("invalid TempHumid data");
//         }
//     }
//     else
//     {
//         Serial.println("ES-Integrate wire loose");
//     }
// }
// 
// void TempHumidRead(void *pvParameters)
// {
//     while (true)
//     {
//         ReadTempHumidSensor(TemperatureRequest, temperature, "Temperature: ");
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//         ReadTempHumidSensor(HumidityRequest, humidity, "Humidity: ");
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//     }
// }
// 
// void TaskTempHumid_init()
// {
//     RS485Serial.begin(9600, SERIAL_8N1, D5, D6); // flip TX-RX if needed
//     xTaskCreate(TempHumidRead, "TempHumidRead", 4096, NULL, 1, NULL);
// }
