int servoPin = 33;
int potPin = 32; 
int trigPin = 18;
int echoPin = 5;
long travel_time;
float Distance;

void setup() {
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 4095, 0, 180);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Angle: ");
  Serial.println(angle);

  Distance = ultrasonic_get_distance();

  Serial.print("Distance: ");
  Serial.println(Distance);

  if (Distance < 10) {
    moveServoTo(angle); 
  } else {
    moveServoTo(0);
  }

  delay(100);
}

void moveServoTo(int angle) {
  int pulseWidth = map(angle, 0, 180, 500, 2500);

  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000 - pulseWidth);
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
