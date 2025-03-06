#include "../src/Headers/ServerTask.h"

const int ledPin = 10;
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}


// Task to handle server
void serverTask(void *pvParameters) {
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    vTaskDelete(NULL);  // Delete the task if SPIFFS initialization fails
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to load Java Script file
  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
    request->send(SPIFFS, "/script.js", "text/javascript");
  });
  
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Handle OTA update
  server.on(
    "/update", HTTP_POST, 
    [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        request->send(response);
        delay(500);
        ESP.restart();
    }, 
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        if (!index) {
            Serial.printf("Starting firmware update: %s\n", filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
                Update.printError(Serial);
            }
        }

        if (Update.write(data, len) != len) {
            Update.printError(Serial);
        }

        if (final) {
            if (Update.end(true)) {
                Serial.println("Update complete!");
            } else {
                Update.printError(Serial);
            }
        }
    }
);

  // Start server
  server.begin();
  ElegantOTA.begin(&server);
  vTaskDelete(NULL);  // Delete the task when done
}

void server_init()
{
  xTaskCreate(serverTask, "ServerTask", 4096, NULL, 1, NULL);
}