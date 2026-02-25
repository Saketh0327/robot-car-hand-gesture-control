# 🖐️ Hand Gesture Controlled Robot Car

Control a car using **hand gestures** detected via a webcam, powered by **MediaPipe**, **Python**, and **ESP32** using **Wifi communication**.

This project combines **Computer Vision** and **Human–Robot Interaction** into a simple but effective real-time control system.

---

## 📌 Overview

The system captures live video from a webcam, detects hand landmarks using MediaPipe, interprets hand gestures in Python, and sends control data to an Arduino or ESP32 through serial communication.

The microcontroller then rotates a servo motor based on the received data.

---

## The project is useful for:
- Human–Robot Interaction
- Robotics
- Gesture-based automation

---
## ⚙️ Tech Stack:
- Python 3.10
- OpenCV 4.9.0.80
- MediaPipe 0.10.8
- ESP32 DEV Modue
- Servo Motor (SG90)
- L298N Motor driver
- 12V DC motors
- Ultra Sonic sensor(HSRC04)
- ESP32 AI Thinker Cam
- 3.7V 18650 Cells x2
- 5V buck converter

---

## 🧠 How It Works:
1. Webcam captures hand movements.
2. MediaPipe detects hand landmarks.
3. Gesture is analyzed in Python.
4. Corresponding command is sent via WIFI.
5. ESP32 receives the command.
6. Corresponding action is performed by the actuators present in the car
7. ESP32 cam if fixed on the servo motor so that, we can get a wider view if needed

---


### 📁 Project Structure


```text
robot-car-hand-gesture-control/
│
├── ESP32_devkit/
│   ├── ESP32_devkit.ino
│    └── README.md
│
├── CameraWebServer/
│   ├── CameraWebServer.ino
│   ├── app_httpd.cpp
│   ├── camera_index.h
│   ├── camera_pins.h
│   └── README.md
│    
│
├── Python/
│   ├── car_control.py
│   └── requirements.txt
│
├── demo/
│   └── demo_video.mp4
│
├── .gitignore
└── README.md
```
---


---

### Hardware Connections
Refer the code in car_control.ino for the pin connection of ESP32

---

## ⚙️ Software Setup
#### 1️⃣ Install Python Dependencies
```
pip install -r Python/requirements.txt
```

#### 2️⃣ Upload Arduino Code
1. Open *Arduino/servo_control.ino*
2. Select the correct Board
3. Select the correct Port
4. Upload the code

#### 3️⃣ Run the Python Script
```
python Python/hand_tracking.py

```
Make sure the correct serial port is set inside the Python file.

___

## ✋ Gesture Control Logic
| Hand Action | Servo Response          |
| ------------------------- | ----------------------- |
| Open Palm           | Move forward  |
| Closed palm               | Moves backward    |
| 3 finger open           | Turns left  |
| 2 finger open           | Turns right  |
| Spider-man gesture           | Servo sweep |
___

## 🚀 Future Improvements:
- Improved smart obstacle avoidance
- Adding LIDAR for mapping
- Preparing a map of a place for autonomous navigation
- Add a portal to select the type of control - button/ hand-gesture/ voice commands


