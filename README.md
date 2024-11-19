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
1. Mai Le Cuong
2. Cao Trung Tin
3. Nguyen Phuoc Thinh

## A few notes before executing project(To be updated):
1. Check if device's COM port can be detected
2. Check MQTT IO_USERNAME and IO_KEY across the project
3. Check Wifi credentials
4. Check power supply for sensors