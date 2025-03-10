#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MAX";
const char* password = "Password";

// GPIO pins for the RGB LED and Buzzer
const int ledRedPin = 16;
const int ledGreenPin = 27;
const int ledBluePin = 14;
const int buzzerPin = 26;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Initialize GPIO pins
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define server routes
  server.on("/light-on", HTTP_GET, []() {
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
    server.send(200, "text/plain", "LED light turned on");
  });

  server.on("/light-off", HTTP_GET, []() {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
    server.send(200, "text/plain", "LED light turned off");
  });

  server.on("/buzzer-on", HTTP_GET, []() {
    digitalWrite(buzzerPin, HIGH);
    server.send(200, "text/plain", "Buzzer turned on");
  });

  server.on("/buzzer-off", HTTP_GET, []() {
    digitalWrite(buzzerPin, LOW);
    server.send(200, "text/plain", "Buzzer turned off");
  });
  
  server.begin();
}

void loop() {
  server.handleClient();
}
