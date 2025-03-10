IoT-Based Sensor Monitoring and Control System

Overview

This project consists of an IoT-based sensor monitoring system with a remote control functionality. It collects data from multiple sensors and sends it to a server, where a separate control unit (ESP32 web server) can respond by activating an LED or buzzer based on the received data.

Components Used

1. Monitoring Node (ESP32-Based Sensor Data Collection)

DHT11 Sensor (Temperature & Humidity) - Pin 26

Light Sensor - Pin 39

RFID Module (MFRC522) - SS_PIN: 5, RST_PIN: 25

Wi-Fi Connectivity (Sends data to DesiredIp/sensor-data)

2. Control Node (ESP32-Based Remote Control System)

RGB LED - Pins: Red (16), Green (27), Blue (14)

Buzzer - Pin 26

ESP32 Web Server for remote contro
