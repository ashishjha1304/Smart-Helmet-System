# 🪖 Smart Helmet System

> A road safety IoT project that prevents accidents by detecting alcohol consumption, drowsiness, and helmet usage — and disabling the bike if safety conditions are not met.

---

## 👨‍💻 Developed By

| Name | Role |
|---|---|
| Ashish Ashutosh Jha | Hardware & Software Development |
| Sneha Singh Anurag Rajput | Hardware & Software Development |

**Institution:** K.M. Agarwal College  
**Program:** B.Sc. IT — Final Year Project

---

## 📹 Demo Video

[▶️ Watch Demo on Google Drive](https://drive.google.com/drive/folders/1P7nhkiHmYQPx73cmg2SPT7c2zzQ3r9jD?usp=sharing)

---

## 📌 About The Project

Road accidents are one of the leading causes of death in India, often caused by drunk driving, drowsiness, and not wearing a helmet. This Smart Helmet System addresses all three issues using sensors, wireless communication, and an automatic bike kill switch.

The system has two units:
- **Helmet Unit (Transmitter)** — worn by the rider, detects safety conditions
- **Bike Unit (Receiver)** — mounted on the bike, takes action based on received data

---

## ⚙️ Features

- 🍺 **Alcohol Detection** — MQ3 sensor detects alcohol level; bike won't start if drunk
- 🪖 **Helmet Detection** — IR sensor checks if helmet is worn before allowing ignition
- 😴 **Drowsiness Detection** — IR sensor monitors eye blink; alerts after 5 seconds of continuous eye closure
- 📡 **Wireless Communication** — NRF24L01 RF module transmits data from helmet to bike
- 🖥️ **LCD Display** — Shows real-time status on bike unit
- 🔔 **Alert System** — LED and Buzzer on both helmet and bike side
- 🔌 **Relay Kill Switch** — Automatically cuts bike motor when unsafe condition detected
- 📶 **Signal Loss Detection** — Bike stops if helmet unit goes out of range

---

## 🛠️ Components Used

### Helmet Side (Transmitter)
| Component | Purpose |
|---|---|
| Arduino Uno | Microcontroller |
| NRF24L01 | Wireless data transmission |
| MQ3 Sensor | Alcohol detection |
| IR Sensor x1 | Helmet worn detection |
| IR Sensor x1 | Drowsiness detection |
| LED | Visual alert on helmet |
| Buzzer | Audio alert on helmet |

### Bike Side (Receiver)
| Component | Purpose |
|---|---|
| Arduino Uno | Microcontroller |
| NRF24L01 | Wireless data reception |
| LCD 16x2 I2C | Status display |
| Relay Module | Motor kill switch |
| LED | Visual alert on bike |
| Buzzer | Audio alert on bike |
| DC Motor | Simulates bike ignition |

---

## 🔌 Wiring

### Transmitter (Helmet Side)
| Component | Arduino Pin |
|---|---|
| MQ3 AO | A0 |
| IR Drowsiness OUT | A1 |
| IR Helmet Worn OUT | A2 |
| LED (+) | D3 |
| Buzzer (+) | D6 |
| NRF24L01 CE | D7 |
| NRF24L01 CSN | D8 |
| NRF24L01 MOSI | D11 |
| NRF24L01 MISO | D12 |
| NRF24L01 SCK | D13 |

### Receiver (Bike Side)
| Component | Arduino Pin |
|---|---|
| LCD SDA | A4 |
| LCD SCL | A5 |
| Relay IN | D3 |
| LED (+) | D5 |
| Buzzer (+) | D6 |
| NRF24L01 CE | D7 |
| NRF24L01 CSN | D8 |
| NRF24L01 MOSI | D11 |
| NRF24L01 MISO | D12 |
| NRF24L01 SCK | D13 |

---

## 📚 Libraries Required

Install these from Arduino IDE → Library Manager:

- `RF24` by TMRh20
- `LiquidCrystal_I2C` by Frank de Brabander

---

## 🚀 How It Works

1. Rider wears helmet — IR sensor detects it
2. MQ3 checks alcohol level at startup
3. If helmet worn AND no alcohol detected → bike starts normally
4. While riding, drowsiness IR sensor continuously monitors eye blink
5. If eyes closed for 5+ seconds → alert triggered, bike stopped
6. All data transmitted wirelessly via NRF24L01 from helmet to bike
7. LCD displays real-time status on bike unit
8. If signal lost (helmet out of range) → bike stops automatically

---

## ⚠️ Conditions That Stop The Bike

| Condition | Action |
|---|---|
| Helmet not worn | Motor OFF + LED + Buzzer |
| Alcohol detected (>200 raw value) | Motor OFF + LED + Buzzer |
| Drowsiness detected (5 sec) | Motor OFF + LED + Buzzer |
| Signal lost | Motor OFF + LED + Buzzer |

---

## 📝 Notes

- NRF24L01 VCC connected to 5V for stable communication
- MQ3 baseline alcohol value ~110-120 (raw); threshold set at 200
- Drowsiness detection uses 5-second continuous eye closure logic to avoid false triggers
- Alcohol sensor test was simulated; sanitizer/perfume can be used for demo

---

## 📄 License

This project was developed for educational purposes as part of B.Sc. IT Final Year curriculum at K.M. Agarwal College.
