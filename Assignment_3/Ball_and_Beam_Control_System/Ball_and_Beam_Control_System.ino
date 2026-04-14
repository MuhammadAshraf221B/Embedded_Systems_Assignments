#include <ESP32Servo.h>

Servo servo;

#define trig 18
#define echo 5

// PID
float kp = 7.0;
float ki = 0.01;
float kd = 3.0;

float prevError = 0;
float sumError = 0;

int center = 40;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  servo.attach(25);
  servo.write(center);
}

// ---------------- LOOP ----------------
void loop() {
  PID();
  delay(100);
}

// ---------------- ULTRASONIC ----------------
float getDistance() {
  static float last = 10;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH, 30000);

  float d = (0.034 * t) / 2;

  if (d > 0) last = d;

  return last;
}

// ---------------- PID ----------------
void PID() {

  float dis = getDistance();

  int setMin = 8;
  int setMax = 11;

  float error = 0;

  if (dis < setMin) {
    error = setMin - dis;
  }
  else if (dis > setMax) {
    error = setMax - dis;
  }
  else {
    error = 0;
    sumError = 0;
  }

  float P = kp * error;

  sumError += error;
  sumError = constrain(sumError, -100, 100);

  float I = ki * sumError;

  float D = kd * (error - prevError);

  float output = P + I + D;

  prevError = error;

  int angle = constrain((int)(center - output), 0, 90);

  servo.write(angle);

  Serial.print("Dist: "); Serial.print(dis);
  Serial.print(" | Error: "); Serial.print(error);
  Serial.print(" | Output: "); Serial.print(output);
  Serial.print(" | Angle: "); Serial.println(angle);
}