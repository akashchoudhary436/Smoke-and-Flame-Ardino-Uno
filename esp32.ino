#define BLYNK_TEMPLATE_ID "TMPL3tN8Ahqo4"  // Your template name
#define BLYNK_DEVICE_NAME "ESP32"  // Your device name
#define BLYNK_AUTH_TOKEN "6U8DRAs14IAAtNP6WORIh7aEMZgXIve9"  // Your Blynk Auth Token
#define BLYNK_TEMPLATE_NAME "ESP32"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>  // Blynk library for ESP32

// Wi-Fi credentials
char ssid[] = "A";              // Your Wi-Fi name
char pass[] = "akash12345";      // Your Wi-Fi password

// Blynk virtual pins
#define VIRTUAL_PIN_SMOKE V1  // Blynk Virtual Pin for Smoke Detection
#define VIRTUAL_PIN_FLAME V2  // Blynk Virtual Pin for Flame Detection

// Set the serial pins for communication between Arduino Uno and ESP32
#define RXD2 16  // ESP32 RX2 pin (for receiving data)
#define TXD2 17  // ESP32 TX2 pin (for sending data)

String sensorData;

void setup() {
  // Initialize Serial for communication with Arduino and Serial Monitor
  Serial.begin(9600);    // For the serial monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Serial communication with Arduino Uno (using RX2/TX2)

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("ESP32 Connected to Blynk and WiFi!");
}

void loop() {
  Blynk.run();  // Keep the Blynk connection alive

  bool smoke_detected = false;
  bool flame_detected = false;

  if (Serial2.available()) {  // If data is available from Arduino Uno
    sensorData = Serial2.readStringUntil('\n');  // Read data from Arduino

    // Check if smoke or flame is detected based on received data
    smoke_detected = sensorData.indexOf("smoke detected") != -1;
    flame_detected = sensorData.indexOf("flame detected") != -1;

    // Debug output to the Serial Monitor
    Serial.println(smoke_detected ? "Smoke detected!" : "No smoke.");
    Serial.println(flame_detected ? "Flame detected!" : "No flame.");
  }

  // Send data to Blynk
  Blynk.virtualWrite(VIRTUAL_PIN_SMOKE, smoke_detected ? 1 : 0);  // 1 if smoke detected, 0 if not
  Blynk.virtualWrite(VIRTUAL_PIN_FLAME, flame_detected ? 1 : 0);  // 1 if flame detected, 0 if not

  delay(1000);  // Delay before checking for new data
}
