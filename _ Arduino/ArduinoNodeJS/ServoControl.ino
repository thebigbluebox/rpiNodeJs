#include <Servo.h>

int sensorPin = A0;       //define variables
int sensorValue = 0;
int magnetPasses = 0;
int calibrate = 10;
int i = 0;
int TURN_TIME = 0;

Servo myservo;    //initialize servo object
int pos = 0;

void setup(){
  Serial.begin(9600);           //initialize serial baudrate
  pinMode(sensorPin, INPUT);    //set sensor input
  myservo.attach(9);            //set servo to pin 9
  myservo.write(90);            // set servo speed to 0
  Serial.println("Hello Tai");
}

void rotateServo(int angle){
  if (angle > 0){             //clockwise rotation
    TURN_TIME = angle * 4.2;  //calculate turn time
    myservo.write(0);         //max speed
    delay(TURN_TIME);
    myservo.write(90);
  }
  if (angle < 0){             //counterclockwise rotation
    TURN_TIME = angle * 4.2 * -1;
    myservo.write(180);
    delay(TURN_TIME);
    myservo.write(90);
  }  
}

void loop(){
  sensorValue = analogRead(sensorPin);    //read sensor data
  
  if (sensorValue < 50){        //magnetic field sensed
    magnetPasses++;
    delay(100);
  }
  
  if (magnetPasses > calibrate){    //1 gallon of water detected
    Serial.println("B1E");
    magnetPasses = 0;
  }
  
  if (Serial.available() > 0){      //input from rpi
    i = Serial.parseInt();
    rotateServo(i);                 //rotate the servo according to input
  }  
}
