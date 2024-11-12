#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>

// --------------------------------------------------------------------------------------------
//        UPDATE CONFIGURATION TO MATCH YOUR ENVIRONMENT
// --------------------------------------------------------------------------------------------

// MQTT connection details
#define MQTT_HOST "test.mosquitto.org"
#define MQTT_PORT 1883
#define MQTT_DEVICEID "esp32-manoj"
#define MQTT_USER "" // no need for authentication, for now
#define MQTT_TOKEN "" // no need for authentication, for now
#define MQTT_TOPIC "esp32-manoj"
#define MQTT_TOPIC_2 "esp32-manoj/humidity"
#define MQTT_TOPIC_COLOR "esp32-manoj/led" 
#define MQTT_TOPIC_DISPLAY "esp32-manoj"

// GPIO pins for devices
#define RED_PIN 19
#define GREEN_PIN 18
#define BLUE_PIN 17
#define DHT_PIN 4

// DHT Sensor type
#define DHTTYPE DHT11

// WiFi credentials
char ssid[] = "POCOF1";
char pass[] = "Manoj1205";

// Instantiate DHT sensor and MQTT client
DHT dht(DHT_PIN, DHTTYPE);
WiFiClient wifiClient;
PubSubClient mqtt(MQTT_HOST, MQTT_PORT, wifiClient);

float h = 0.0; // humidity
float t = 0.0; // temperature

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] : ");
  payload[length] = 0; // zero-terminate payload
  Serial.println((char *)payload);

  // Check if the message is for the LED color control topic
  if (strcmp(topic, MQTT_TOPIC_COLOR) == 0) {
    // Control LED color based on received message
    if (strcmp((char *)payload, "red") == 0) {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
    } else if (strcmp((char *)payload, "green") == 0) {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
    } else if (strcmp((char *)payload, "blue") == 0) {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
    } else if (strcmp((char *)payload, "off") == 0) {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  Serial.println("ESP32 Sensor Application");

  // WiFi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // Start connected devices
  dht.begin();
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Connect to MQTT broker
  mqtt.setCallback(callback); // Set the callback function for incoming messages
  if (mqtt.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
    Serial.println("MQTT Connected");
    mqtt.subscribe(MQTT_TOPIC_DISPLAY);
    mqtt.subscribe(MQTT_TOPIC_COLOR); // Subscribe to color control topic
  } else {
    Serial.println("MQTT Failed to connect!");
    ESP.restart();
  }
}

void loop() {
  mqtt.loop();
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqtt.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
      Serial.println("MQTT Connected");
      mqtt.subscribe(MQTT_TOPIC_DISPLAY);
      mqtt.subscribe(MQTT_TOPIC_COLOR); // Re-subscribe to color control topic
      mqtt.loop();
    } else {
      Serial.println("MQTT Failed to connect!");
      delay(1000);
    }
  }

  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Set RGB LED Colour based on temp (if not overridden by color messages)
    if (t > 30) {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
    } else {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
    }

    // Prepare message to publish
    char tempmsg[100];
    char hummsg[100];
    sprintf(tempmsg, "%.2f", t);
    sprintf(hummsg, "%.2f", h);
    Serial.println(tempmsg);
    Serial.println(hummsg);
    

    // Publish the message
    if (!mqtt.publish(MQTT_TOPIC, tempmsg)) {
      Serial.println("MQTT Publish failed for temperature");
    }
    if (!mqtt.publish(MQTT_TOPIC_2, hummsg)) {
      Serial.println("MQTT Publish failed for humidity");
    }
  }
  
  // Keep polling MQTT for incoming messages
  for (int i = 0; i < 10; i++) {
    mqtt.loop();
    delay(1000);
  }
}
