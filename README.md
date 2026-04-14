![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![Platform](https://img.shields.io/badge/platform-STM32%20%7C%20ESP32%20%7C%20Flutter-blue)

---

## 🧠 Project Overview

This is a planned embedded systems project to build a **mobile-controlled RC car** using STM32, ESP32, and a Flutter application.

The goal is to design a **modular system** where each component has a clear role:

- 📱 Flutter app → user control interface
- 📡 ESP32 → Bluetooth communication bridge
- ⚙️ STM32 → real-time motor control
- 🔧 TB6612 motor driver → motor actuation

---

## 🏗️ Planned System Design

The system will work as follows:

1. A mobile app sends control commands (Forward, Backward, Left, Right, Stop).
2. ESP32 receives commands via Bluetooth.
3. ESP32 forwards commands to STM32 using UART communication.
4. STM32 processes commands and generates motor control signals.
5. TB6612 motor driver drives the DC motors accordingly.

---

## 🎮 Command System (Planned)

The system will use simple character-based commands:

- `F` → Move Forward  
- `B` → Move Backward  
- `L` → Turn Left  
- `R` → Turn Right  
- `S` → Stop  

Future upgrade idea:
- Add speed control using values like `F100`

---

## 🔌 Hardware Components (Planned)

- STM32 microcontroller (main control unit)
- ESP32 module (Bluetooth communication)
- TB6612FNG motor driver
- DC motors + chassis
- Battery system for motors and logic

---

## 🔗 Communication Flow

- Flutter app → ESP32 (Bluetooth)
- ESP32 → STM32 (UART serial)
- STM32 → TB6612 (GPIO + PWM signals)
- TB6612 → Motors

---

## ⚙️ Planned Features

- Mobile-based RC control
- Bluetooth communication (ESP32)
- UART bridge between ESP32 and STM32
- Motor direction control (basic movement)
- Modular firmware design for future upgrades

---

## 🚀 Future Improvements

This project is planned to evolve into:

- ESP32-CAM integration for live video streaming
- WiFi control option
- Joystick-based mobile control UI
- Speed control using PWM
- Obstacle detection using sensors
- Autonomous driving mode

---

## 🧠 Learning Goals

This project is being built to learn:

- Embedded systems (STM32 firmware development)
- Communication protocols (UART, Bluetooth)
- Motor control using PWM
- ESP32 networking / Bluetooth
- Mobile app development with Flutter
- Full system-level embedded architecture

---

## 👨‍💻 Status

This project is currently in the **planning and development phase**.  
Hardware setup and software development are in progress.

---

## 📌 Notes

- The architecture may change during implementation.
- Initial version will focus on basic Bluetooth control and motor movement.
- Features will be added step-by-step as development progresses.
