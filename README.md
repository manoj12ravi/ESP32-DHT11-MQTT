ESP32 MQTT DHT11 Project
This project demonstrates how to use an ESP32 microcontroller to:

Read temperature and humidity data from a DHT11 sensor.
Publish sensor data to an MQTT broker.
Control an RGB LED via MQTT messages.
Table of Contents
Features
Components
Prerequisites
Configuration
WiFi Credentials
MQTT Broker Settings
Pin Configuration
Topics Used
How to Use
Clone This Repository
Open the Code in Arduino IDE
Update Configurations
Upload the Code
Interact via MQTT
Example MQTT Commands
Troubleshooting
Future Enhancements
License
Features
Publish temperature and humidity readings to MQTT topics.
Change LED colors based on MQTT messages.
Automatically adjust LED color based on temperature thresholds.
Components
ESP32 Microcontroller
DHT11 Temperature and Humidity Sensor
RGB LED
MQTT Broker (e.g., broker.mqtt.cool)
Prerequisites
Arduino IDE installed.
Required libraries:
WiFi.h
DHT.h
PubSubClient.h
An active MQTT broker.
Configuration
1. WiFi Credentials
Update your WiFi SSID and password in the code:

cpp
Copy code
char ssid[] = "your-SSID";
char pass[] = "your-password";
2. MQTT Broker Settings
Update the MQTT broker details:

cpp
Copy code
#define MQTT_HOST "broker.mqtt.cool"
#define MQTT_PORT 1883
3. Pin Configuration
Update the pin configurations for the RGB LED and DHT11 sensor:

cpp
Copy code
#define RED_PIN 19
#define GREEN_PIN 18
#define BLUE_PIN 17
#define DHT_PIN 4
Topics Used
Temperature Topic: esp32-manoj – Publishes temperature data.
Humidity Topic: esp32-manoj/humidity – Publishes humidity data.
LED Control Topic: esp32-manoj/led – Receives commands to control the RGB LED.
How to Use
1. Clone This Repository
bash
Copy code
git clone https://github.com/<your-username>/ESP32-MQTT-DHT11.git
2. Open the Code in Arduino IDE
Ensure you have the necessary libraries installed:

WiFi.h
DHT.h
PubSubClient.h
3. Update Configurations
Modify the WiFi, MQTT, and pin configurations in the code to match your setup.

4. Upload the Code
Compile and upload the code to your ESP32 board using the Arduino IDE.

5. Interact via MQTT
You can control the LED and receive sensor data by subscribing to or publishing messages on the MQTT topics.

Example MQTT Commands
Set LED to Red
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj/led" -m "red"
Set LED to Green
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj/led" -m "green"
Publish Temperature Data
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj" -m "25.0"
Troubleshooting
MQTT Connection Issues:
Ensure the MQTT broker is reachable.
Double-check your WiFi credentials.
Sensor Read Errors:
Verify the DHT11 sensor wiring.
Ensure the sensor is functioning properly.
LED Not Responding:
Check if correct pins are used.
Confirm the LED control topic receives messages.
Future Enhancements
Add support for multiple sensors.
Implement more advanced control features, such as dynamic thresholds for LED changes.
Integrate a web interface for easier control and monitoring.
Use secure MQTT (TLS/SSL) for encrypted communication.