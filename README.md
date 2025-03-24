# 📡 IoT Monitoring and Control System – Dual Node Architecture

This project implements a two-node IoT system using Arduino-compatible devices. It features a **monitoring node** that collects environmental data and a **control node** that reacts based on the received sensor information.

---

## 🔁 System Overview

### 🧠 Nodes

- **Monitoring Node** (`monitoring_node.ino`)
  - Gathers data (e.g., temperature, humidity, light, gas levels)
  - Sends periodic updates to the control node (via serial, RF, WiFi, or LoRa)

- **Control Node** (`control_node.ino`)
  - Receives sensor data
  - Makes real-time decisions: e.g., turn on fan, buzzer, lights, or send alerts

---

## 📦 Features

- 🌡️ Real-time environmental monitoring
- 🔁 Communication between nodes (custom protocol or wireless)
- 🚨 Smart automated actions (alerts, devices, logging)
- 🧠 Modular and easy to extend for other sensor types

---

## 🧰 Hardware Requirements

- 2x ESP32 / Arduino boards  
- DHT11/DHT22 for temperature & humidity  
- MQ2/MQ135 for gas detection  
- LDR for light sensing  
- Buzzer / Fan / LEDs for output control  
- Wireless modules (e.g., LoRa, nRF24L01, WiFi) for communication

---

## 🔌 Suggested Wiring

**Monitoring Node**  
- DHT sensor to digital pin  
- Gas sensor to analog pin  
- LDR to analog pin

**Control Node**  
- Relay / fan / buzzer connected to output pins  
- Communication module connected via SPI/I2C/UART

---

## 🛠 Setup

1. Upload `monitoring_node.ino` to the data collection board
2. Upload `control_node.ino` to the controller board
3. Power both devices
4. View data via Serial Monitor or connected dashboard

---

## 📈 Future Improvements

- 🔗 Add MQTT / HTTP API for cloud logging
- 📊 Build dashboard with Node-RED or Grafana
- 🔐 Add data encryption and authentication
- 🧠 Add machine learning for smarter control decisions

---

## 📬 Contact

Feel free to open issues or pull requests to contribute. Hardware photos, wiring diagrams, or data logs are welcome!

