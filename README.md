## Libraries:
- ESPAsyncWebServer
- Adafruit_MQTT_Library
- Publish/Subscribe Client
- SPIFFs

## Manual:
1. Enter Bootloader by Hold Boot -> Hold Reset -> Release Reset - > Release Boot.
2. Upload Filesystem Image Using Platformio.
3. Flash Firmware.
4. Exit Bootloader by Pressing Reset.
5. To build and upload filesystem image (SPIFF): Platformio Extension -> "Build Filesystem Image" -> "Upload Filesystem Image"

## Members:
1. Nguyen Phuoc Thinh
2. Mai Le Cuong

## A few notes before executing project(To be updated):
1. Check if device's COM port can be detected
2. Check MQTT IO_USERNAME and IO_KEY across the project
3. Check Wifi credentials
4. Check power supply for sensors
5. Check if project_config.h is available for condition 2 and 3 above
6. Check script.js inside data folder for device Webserver display (optional)
7. Check Global_config.h and platformio.ini to make sure no library is missing
8. Check Ultrasonic sensor related info before using as this is advanced feature