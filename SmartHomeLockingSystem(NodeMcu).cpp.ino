#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>

// Wi-Fi credentials
#define WIFI_SSID "Anushka"
#define WIFI_PASSWORD "Your_PASSWORD"

// Firebase credentials
#define FIREBASE_HOST "https://console.firebase.google.com/project/smarthomelock-7d0c8/database/smarthomelock-7d0c8-default-rtdb/data/~2F"
#define FIREBASE_AUTH "your_firebase_secret"

// Pin for servo motor
Servo lockServo;
int servoPin = D4;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to Wi-Fi");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  lockServo.attach(servoPin);
  lockServo.write(0); // Locked position
}

void loop() {
  String request = Firebase.getString("/UNLOCK/unlock_request");
  Serial.println("Unlock request: " + request);

  if (request == "otp" || request == "manual") {
    // Unlock the door
    lockServo.write(90); // Unlocked position
    Firebase.setString("/UNLOCK/status", "unlocked");
    delay(5000); // Keep unlocked for 5 seconds
    lockServo.write(0); // Lock again
    Firebase.setString("/UNLOCK/status", "locked");
    Firebase.setString("/UNLOCK/unlock_request", "none");
  }

  delay(2000); // Check every 2 seconds
}
