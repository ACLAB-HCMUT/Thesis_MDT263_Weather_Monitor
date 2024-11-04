// Space for defining necessary components

// DEFINE WIFI CREDENTIALS
#define PROJECT_WIFI_SSID "ACLAB"
#define PROJECT_WIFI_PASSWORD "ACLAB2023"

// DEFINE MOST-USED DELAY
#define delay_minute 60000
#define delay_relay 100
#define delay_temp 12000
#define delay_connect 100
#define delay_wifi 1000
#define general_delay 2000

// DEFINE MQTT
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883
#define IO_USERNAME "ThinhNguyen1801"
#define IO_KEY "" // Feed key goes here

// DEFINE RELAY
#define TXD_RELAY 6
#define RXD_RELAY 7
#define SDA_PIN 11
#define SCL_PIN 12
#define BUFFER_SIZE 256 // DECREASE for low latency or INCREASE for more space || Range: [32, 1024]