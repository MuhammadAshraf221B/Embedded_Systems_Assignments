#include <ESP32Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

Servo myServo;
int servoPin = 18;
int servoPos = 0;

int trigPin = 25;
int echoPin = 5;
long travel_time;
float Distance;

void setup() {
  myServo.attach(servoPin);

  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {

  Distance = ultrasonic_get_distance();

  if(Distance < 10 && servoPos < 90){
    openDoor();
  }else if(Distance >= 10 && servoPos > 0){
    closeDoor();
  }
  lcd.setCursor(0,0);
  if(servoPos == 90)
    lcd.print("State: OPEN   ");
  else
    lcd.print("State: CLOSED ");

  lcd.setCursor(0,1);
  lcd.print("Dist: ");
  lcd.print(Distance, 1);
  lcd.print(" cm   ");

  Serial.println(Distance);
}

void openDoor(){
  while(servoPos < 90){
    servoPos = servoPos + 2;
    myServo.write(servoPos);
    delay(30);
  }
}

void closeDoor(){
  while(servoPos > 0){
    servoPos = servoPos - 2;
    myServo.write(servoPos);
    delay(30);
  }
}

float ultrasonic_get_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  travel_time = pulseIn(echoPin, HIGH);
  Distance = (0.034 * travel_time) / 2;
  return Distance;
}