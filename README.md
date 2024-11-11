# ESP32-DHT11-MQTT
 "ESP32 project for publishing DHT11 sensor data and controlling LED via MQTT"

|\ \ \ \ \ \ \ \ \ \ \ \ 
|\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 
|\ \ \ \ \ \ \ \ \ \ \ \ \  \ \ \ \ \ \ \ \ 
|\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \
|\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \

ESP32 MQTT DHT11 Project
This project demonstrates how to use an ESP32 microcontroller to:

Read temperature and humidity data from a DHT11 sensor.
Publish sensor data to an MQTT broker.
Control an RGB LED via MQTT messages.
Features
Publish temperature and humidity readings to specific MQTT topics.
Dynamically control LED color through MQTT messages.
Automatically adjust LED color based on temperature thresholds.
Components
ESP32 Microcontroller
DHT11 Temperature and Humidity Sensor
RGB LED (3 pins: Red, Green, Blue)
MQTT Broker (e.g., broker.mqtt.cool)
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
Ensure your pin configurations match your hardware setup:

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
Ensure the following libraries are installed:

WiFi.h
DHT.h
PubSubClient.h
3. Update Configurations
Modify the WiFi, MQTT, and pin configurations in the code to match your setup.

4. Upload the Code
Compile and upload the code to your ESP32 board using the Arduino IDE.

5. Interact via MQTT
Use any MQTT client to interact with your ESP32 device:

Publish commands to control the LED.
Subscribe to temperature and humidity topics to monitor sensor data.
Example MQTT Commands
1. Set LED to Red:
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj/led" -m "red"
2. Set LED to Green:
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj/led" -m "green"
3. Publish Temperature Data:
bash
Copy code
mosquitto_pub -h broker.mqtt.cool -t "esp32-manoj" -m "25.0"
Troubleshooting
1. MQTT Connection Issues:
Ensure the MQTT broker is reachable, and credentials are correct.
Verify that the MQTT broker supports anonymous connections or configure user authentication.
2. WiFi Connectivity:
Double-check your SSID and password.
Ensure your router is online and within range.
3. Sensor Data:
Verify the DHT11 sensor connections (power, ground, data).
If readings are inconsistent, try using a pull-up resistor on the data pin.
Future Enhancements
Add support for multiple sensors.
Implement secure MQTT connections using TLS.
Integrate with cloud services for data logging and visualization.
