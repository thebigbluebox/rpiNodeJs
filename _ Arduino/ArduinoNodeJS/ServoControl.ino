#include <Servo.h>

int sensorPin = A0;
int sensorValue = 0;
int magnetPasses = 0;
int calibrate = 15;

Servo myservo;
int pos = 0;

void setup(){
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  myservo.attach(9);
}

void loop(){
  sensorValue = analogRead(sensorPin);
  
  if (sensorValue < 50){
    magnetPasses++;
  }
  
  Serial.println(sensorValue);
  delay(100);
  
  if (magnetPasses > calibrate){
    Serial.println(1);
    magnetPasses = 0;
  }

  for (pos = 0; pos <= 180; pos += 1){['
    myservo.write(pos);
    delay(15);  
  }
  for (pos = 0; pos >= 0; pos -= 1){
    myservo.write(pos);
    delay(15);  
  }
    
}
