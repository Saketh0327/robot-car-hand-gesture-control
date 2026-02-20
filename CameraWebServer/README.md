# 📷 ESP32-CAM Web Server

This module runs a live MJPEG streaming web server on the ESP32-CAM.  
It creates a WiFi access point and allows real-time video streaming through a browser.

This camera module is used in the **Robot Car Hand Gesture Control** project as the vision input system.

---

## 🚀 Features

- 📡 Creates its own WiFi network (`ESP32_GESTURE`)
- 🎥 Live camera streaming via browser
- 🔦 Optional LED flash support
- 📷 Flexible resolution 

---

## 📡 Default WiFi Credentials
SSID: ESP32_GESTURE
Password: 12345678


After uploading the code:

1. Power the ESP32-CAM
2. Connect to the WiFi network `ESP32_GESTURE`
3. Open your browser
4. Visit the url which you will obtain as the output in the Arduino IDE when ESP32 cam is connected to PC via serial


