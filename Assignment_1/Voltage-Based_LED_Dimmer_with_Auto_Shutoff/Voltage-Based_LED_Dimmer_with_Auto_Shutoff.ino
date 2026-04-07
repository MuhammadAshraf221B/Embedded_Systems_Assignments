int readPin = 34;
int LED_pin = 13;
int buttonPin = 25;

int readValue;
float voltage;
float Vin;

unsigned long highStartTime = 0;
bool highZone = false;
bool systemOn = false;
bool buttonPressed = false;


void setup() {
  pinMode(readPin, INPUT);
  pinMode(LED_pin, OUTPUT);
   pinMode(buttonPin, INPUT_PULLUP);
   Serial.begin(9600);
}

void loop() {

  if(digitalRead(buttonPin) == LOW && !buttonPressed){
    systemOn = !systemOn;  
    buttonPressed = true;
    delay(200); 
  }
  if(digitalRead(buttonPin) == HIGH){
    buttonPressed = false;
  }

  if(!systemOn){
    analogWrite(LED_pin,0);  
    return;                   
  }
  readValue = analogRead(readPin);
  voltage = readValue * 3.3/4095.;
  Vin = (readValue * 255) / 4095;
  Serial.println(voltage);

  if(voltage < 1){
    // Low speed
    analogWrite(LED_pin, Vin);
    delay(2000);
    analogWrite(LED_pin, 0);
    delay(2000);
  }
  else if(voltage < 2.3){
    // Medium speed
    analogWrite(LED_pin, Vin);
  }
  else{
    // High speed
    analogWrite(LED_pin, Vin);
    delay(500);
    analogWrite(LED_pin, 0);
    delay(500);

    if(!highZone){
      highZone = true;
      highStartTime = millis();
    }

    if(millis() - highStartTime > 5000){

      for(int i=0;i<3;i++){
        analogWrite(LED_pin,255);
        delay(100);
        analogWrite(LED_pin,0);
        delay(100);
      }

      analogWrite(LED_pin, 0);
      systemOn = false;
      highZone = false; 
    }

  }


}

