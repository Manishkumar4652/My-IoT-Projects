# 🚨 ESP8266 Ultrasonic Security System with Telegram Alerts

This project uses an **ESP8266 (NodeMCU)** and an **HC-SR04 ultrasonic sensor** to create a real-time **security alert system**.  
Whenever a person/object comes within **20 cm**, the system:

- Activates a **buzzer**
- Turns on an **LED**
- Sends an instant **Telegram alert message** through your bot

This makes it useful for **home security**, **door monitoring**, and **intrusion detection**.

---

## 🛠️ Features

- 🔔 Buzzer + LED alert on motion detection  
- 📲 Sends Telegram message using HTTPS  
- 📡 Real-time distance monitoring  
- 🔌 Simple wiring  
- 🌐 Works through WiFi hotspot  
- 🛡️ Uses secure TLS connection (`WiFiClientSecure`)

---

## 📦 Hardware Required

- ESP8266 NodeMCU  
- HC-SR04 Ultrasonic Sensor  
- Active Buzzer  
- LED + 220Ω resistor  
- Jumper wires  
- Power supply / USB  

---

## 🔌 Wiring Diagram

### **HC-SR04 → ESP8266**

| Sensor Pin | ESP8266 Pin |
|-----------|-------------|
| VCC       | 5V (or Vin) |
| GND       | GND         |
| TRIG      | D5          |
| ECHO      | D6          |

> ⚠ The Echo pin outputs 5V. ESP8266 uses 3.3V logic. Although it often works, it is recommended to use a **1K + 2K voltage divider** on the ECHO line.

---

### **Buzzer → ESP8266**

| Buzzer Pin | ESP8266 Pin |
|-----------|-------------|
| +         | D7          |
| –         | GND         |

---

### **LED → ESP8266**

| LED Pin | ESP8266 Pin |
|---------|-------------|
| + (Anode) | D4 |
| – (Cathode) | GND (via 220Ω resistor) |

---

## 📝 How It Works

1. ESP8266 connects to WiFi.
2. HC-SR04 continuously measures distance.
3. If distance < **20 cm**:
   - Buzzer ON  
   - LED ON  
   - Telegram alert sent instantly  
4. Otherwise:
   - Buzzer OFF  
   - LED OFF  
5. Distance is printed on Serial Monitor.

---

## 💬 Telegram Bot Setup

1. Open Telegram → Search **BotFather**
2. Create bot using `/newbot`
3. Copy the **Bot Token**
4. Get Chat ID:
