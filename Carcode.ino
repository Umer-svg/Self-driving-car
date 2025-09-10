#include <AFMotor.h>
#include <Servo.h>

// Motor setup
AF_DCMotor motor1(1); // M1 - Front Left
AF_DCMotor motor2(2); // M2 - Back Left
AF_DCMotor motor3(3); // M3 - Front Right
AF_DCMotor motor4(4); // M4 - Back Right

// Sensor pins
#define trigPin A0
#define echoPin A1

// Servo
Servo myServo;

// Distance values
int distance, leftDistance, rightDistance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(10);
  myServo.write(90); // center

  setSpeedAll(200); // Default speed
}

void loop() {
  distance = getDistance();

  if (distance < 20) {
    stopAll();
    delay(500);
    checkSurroundings();
  } else {
    moveForward();
  }
}

// === Functions ===

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // cm
}

void checkSurroundings() {
  myServo.write(0); delay(500);
  leftDistance = getDistance();

  myServo.write(180); delay(500);
  rightDistance = getDistance();

  myServo.write(90); delay(300);

  if (leftDistance > rightDistance) {
    turnLeft();
  } else {
    turnRight();
  }
}

void moveForward() {
  setSpeedAll(200);
  motor1.run(FORWARD);   // M1 - Front Left
  motor2.run(FORWARD);  // M2 - Back Left
  motor3.run(FORWARD);   // M3 - Front Right
  motor4.run(FORWARD);  // M4 - Back Right
}

void turnLeft() {
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(BACKWARD);   // M1 - Front Left (reverse)
  motor2.run(BACKWARD);    // M2 - Back Left
  motor3.run(FORWARD);    // M3 - Front Right
  motor4.run(FOREARD);   // M4 - Back Right

  delay(600);
  stopAll();
}

void turnRight() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(100);
  motor4.setSpeed(100);

  motor1.run(FORWARD);    // M1 - Front Left
  motor2.run(FORWARD);   // M2 - Back Left
  motor3.run(BACKWARD);   // M3 - Front Right (reverse)
  motor4.run(BACKWARD);    // M4 - Back Right

  delay(600);
  stopAll();
}

void stopAll() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void setSpeedAll(int speed) {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}
