#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "MAX";
const char* password = "Password";
const char* serverAddress = "DesiredIp/sensor-data";

// DHT setup
#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Light sensor setup
const int lightPin = 39;

// RFID reader (MFRC522) setup
#define RST_PIN  25
#define SS_PIN   5
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Variable to keep track of RFID reading
bool isCardDetected = false;

// Rate of reading data from sensors
const int refreshRate = 500;

void setup() {
    Serial.begin(115200);
    
    // Initialize DHT sensor
    dht.begin();
    
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    // Initialize MFRC522
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522

    // Initialize GPIO
    pinMode(lightPin, INPUT);
}

void loop() {
    String jsonPayload = createJsonPayload();

    sendSensorDataToManager(jsonPayload);
    
    delay(refreshRate);
}

String createJsonPayload(){
    // Get temperature reading
    float temperature = dht.readTemperature();
    
    // Get light reading
    int lightLevel = analogRead(lightPin);
    
    // Check for a new card
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        isCardDetected = true;

        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
    } else {
        isCardDetected = false;
    }

    // Create JSON string
    String payload = "{\"temperature\":" + String(temperature, 2) + ",";
    payload += "\"light\":" + String(lightLevel) + ",";
    payload += "\"isCardDetected\":" + String(isCardDetected ? "true" : "false") + "}";
    
    return payload;
}

void sendSensorDataToManager(String jsonPayload) {
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        
        http.begin(serverAddress);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonPayload);

        if(httpResponseCode > 0){
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        }
        else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }
    else {
        Serial.println("WiFi Disconnected");
    }
}
