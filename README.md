# 🚗 Voice Controlled Car with Obstacle Detection and ESP32-CAM

A smart robotic car controlled using voice commands through Bluetooth, equipped with ultrasonic obstacle detection and ESP32-CAM based real-time video streaming.

## 📌 Project Overview

The Voice Controlled Car is an embedded robotics project that allows a user to control a robotic vehicle using voice commands from a smartphone. The voice command is transmitted through an HC-05 Bluetooth module to an Arduino UNO. The Arduino processes the command and controls the DC motors through an L298N motor driver. HC-SR04 ultrasonic sensors continuously monitor the surroundings and prevent the car from moving when an obstacle is detected. An ESP32-CAM is mounted on the vehicle to provide real-time video visualization through a Wi-Fi web server.

## ✨ Features

- 🎙️ Voice-controlled movement
- 📱 Bluetooth communication
- 🚗 Forward, backward, left and right movement
- 🛑 Stop control
- 🚧 Front and rear obstacle detection
- 🔊 Buzzer warning
- 📷 ESP32-CAM real-time video streaming
- 🌐 Wi-Fi-based camera visualization
- ⚡ PWM-based motor speed control
- 🔧 Embedded systems and robotics integration

## 🧠 System Architecture

```text
                     ┌─────────────────┐
                     │   Smartphone    │
                     │ Voice Commands  │
                     └────────┬────────┘
                              │
                         Bluetooth
                              │
                              ▼
                     ┌─────────────────┐
                     │      HC-05      │
                     └────────┬────────┘
                              │
                              ▼
                     ┌─────────────────┐
                     │   Arduino UNO   │
                     │                 │
                     │ Command Control │
                     │ Obstacle Sensor │
                     └────────┬────────┘
                              │
                              ▼
                     ┌─────────────────┐
                     │      L298N      │
                     │  Motor Driver   │
                     └────────┬────────┘
                              │
                       ┌──────┴──────┐
                       ▼             ▼
                   DC Motor 1    DC Motor 2


              ┌──────────────────────┐
              │      ESP32-CAM       │
              │ Camera + Wi-Fi       │
              └──────────┬───────────┘
                         │
                        Wi-Fi
                         │
                         ▼
                ┌──────────────────┐
                │ Phone / Laptop   │
                │ Web Browser      │
                │ Live Video       │
                └──────────────────┘

