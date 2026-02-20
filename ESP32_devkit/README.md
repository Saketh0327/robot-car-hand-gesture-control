# ESP32 car control

## 🚀 Features: 
- Creates its own WiFi Access Point
- Receives movement commands via UDP
- Controls two DC motors (L298N or similar driver)
- Uses an Ultrasonic Sensor for obstacle detection
- Performs a non-blocking servo sweep action
- Automatically stops when an obstacle is detected

---
## Connections:
  ### Motor driver pins
  | Function | ESP32 Pin |
|----------|-----------|
| IN1      | 26        |
| IN2      | 27        |
| ENA      | 14        |
| IN3      | 25        |
| IN4      | 33        |
| ENB      | 13        |
 
   ### Ultrasonic pins
| Function | ESP32 Pin |
|----------|-----------|
| TRIG     | 19        |
| ECHO     | 18        |

   ### Servo pins
| Function | ESP32 Pin |
|----------|-----------|
| Signal   | 5         |


---



