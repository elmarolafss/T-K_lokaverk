#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int buttonPin = 2;
int pos = 0;    // variable to store the servo position
int potient = A0;
int potientValue = 0;
int programState = 0;
int buttonState = HIGH;
int buttonAdur = LOW;
int trigPin = 6;
int echoPin = 5;
int servoPin = 9;
int led = 3;
int servoValue = 0;
int servoStep = 1;
int cm;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potient, INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop() {
  potientValue = analogRead(potient);
  potientValue = map(potientValue, 0, 1023, 0, 180);
  buttonState = digitalRead(buttonPin);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  cm = pulseIn(echoPin,HIGH)/58.0;  
  cm = (int(cm * 100.0))/100.0;
  if(cm < 0)
  {
    cm = 0;
  }
  if (servoValue == 180) {
    servoStep = -1;
  }
  else if (servoValue == 0) {
    servoStep = 1;
  }
  if (buttonState == HIGH && buttonAdur == LOW) {
    if (programState == 0) {
      programState = 1;
    }
    else if (programState == 1) {
      programState = 0;
    }
  }
  if (programState == 0) {
    myservo.write(potientValue);
  }
  else if (programState == 1) {
    myservo.write(servoValue);
  }
  if (cm < 20) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  delay(15);
  Serial.println(cm);
  servoValue += servoStep;
  buttonAdur = buttonState;
}
