#include <WiFi.h>
#include <FirebaseESP32.h>
#include "esp_camera.h"

// Wi-Fi credentials
#define WIFI_SSID "Anushka"
#define WIFI_PASSWORD "Your_PASSWORD"

// Firebase
#define FIREBASE_HOST "https://console.firebase.google.com/project/smarthomelock-7d0c8/database/smarthomelock-7d0c8-default-rtdb/data/~2F"
#define FIREBASE_AUTH "your_firebase_secret"

FirebaseData firebaseData;

void startCameraServer(); // Optional: if you're using camera stream

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Initialize camera
  camera_config_t config;
  // (setup your ESP32-CAM config here based on board, frame size, etc.)
  esp_camera_init(&config);

  // Face Recognition logic...
  // If face is recognized:
  Firebase.setString(firebaseData, "/UNLOCK/unlock_request", "face");
  Firebase.setString(firebaseData, "/UNLOCK/status", "unlocked");
  delay(5000);
  Firebase.setString(firebaseData, "/UNLOCK/status", "locked");
  Firebase.setString(firebaseData, "/UNLOCK/unlock_request", "none");
}

void loop() {
  // Your face recognition detection loop
}
