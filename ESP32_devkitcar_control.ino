#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESP32Servo.h>

// SERVO
#define SERVO_PIN 5   // SAFE pin for ESP32 servo
#define SERVO_CENTER 90
#define SERVO_LEFT   0
#define SERVO_RIGHT  180

Servo servo;
bool servoBusy = false;
unsigned long servoTimer = 0;
int servoStage = 0;

// MOTOR PINS 
#define IN1 26
#define IN2 27
#define ENA 14

#define IN3 25
#define IN4 33
#define ENB 13

int speedLeft  = 200;
int speedRight = 200;

// ULTRASONIC 
#define TRIG_PIN 19
#define ECHO_PIN 18
#define OBSTACLE_DISTANCE 20   // cm

// WIFI
WiFiUDP udp;
const int port = 4210;

// FUNCTION DECLARATIONS
long getDistanceCM();
void forward();
void backward();
void left();
void right();
void stopMotors();
void startServoSweep();
void updateServoSweep();

// SETUP
void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Wi-Fi AP
  WiFi.softAP("ESP32_GESTURE", "12345678");
  udp.begin(port);

  // Servo
  servo.attach(SERVO_PIN, 500, 2400);
  servo.write(SERVO_CENTER);

  stopMotors();
}
void loop() {

  updateServoSweep();

  // ALWAYS CHECK DISTANCE 
  long distance = getDistanceCM();
  bool obstacle = (distance > 0 && distance < OBSTACLE_DISTANCE);

  Serial.print("Distance: ");
  Serial.println(distance);

  static char cmd = 'S';  // store last command

  // CHECK IF NEW UDP PACKET
  int packetSize = udp.parsePacket();
  if (packetSize) {
    udp.read(&cmd, 1);
    Serial.print("CMD: ");
    Serial.println(cmd);
  }

  // SERVO
  if (cmd == 's' && !servoBusy) {
    startServoSweep();
  }

  // MOVEMENT LOGIC
  if (cmd == 'F') {
    if (!obstacle) forward();
    else {
      Serial.println("Blocked!");
      stopMotors();
    }
  }
  else if (cmd == 'B') backward();
  else if (cmd == 'R') right();
  else if (cmd == 'L') left();
  else stopMotors();
}



// SERVO SWEEP LOGIC
void startServoSweep() {
  servoBusy = true;
  servoStage = 0;
  servoTimer = millis();
  servo.write(SERVO_LEFT);
}

void updateServoSweep() {
  if (!servoBusy) return;

  unsigned long now = millis();

  // Left → Right (slow)
  if (servoStage == 0 && now - servoTimer > 1200) {
    servo.write(SERVO_RIGHT);
    servoStage = 1;
    servoTimer = now;
  }
  // Right → Center (slow)
  else if (servoStage == 1 && now - servoTimer > 1500) {
    servo.write(SERVO_CENTER);
    servoStage = 2;
    servoTimer = now;
  }
  // Finish
  else if (servoStage == 2 && now - servoTimer > 1000) {
    servoBusy = false;
  }
}


//  MOTOR FUNCTIONS
void forward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}

void backward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}

void left() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ULTRASONIC
long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);

  if (duration == 0) return -1;

  long distance = duration / 58;

  if (distance <= 0 || distance > 400)
    return -1;

  return distance;
}

