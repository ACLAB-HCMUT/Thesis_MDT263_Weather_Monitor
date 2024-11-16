#include "../src/Headers/WifiTask.h"

const char* ssid = PROJECT_WIFI_SSID;
const char* password = PROJECT_WIFI_PASSWORD;

void wifiTask(void *pvParameters) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(delay_wifi / portTICK_PERIOD_MS);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  vTaskDelete(NULL);
}

void wifi_init(){
    xTaskCreate(wifiTask, "WiFiTask", 4096, NULL, 1, NULL);
}