#include <Servo.h>

int sensorPin = A0;
int sensorValue = 0;
int magnetPasses = 0;
int calibrate = 10;
int i = 0;
int TURN_TIME = 0;

Servo myservo;
int pos = 0;

void setup(){
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  myservo.attach(9);
  myservo.write(90);
  Serial.println("BHello TaiE");
}

void rotateServo(int angle){
  if (angle > 0){
    TURN_TIME = angle * 4.2;
    myservo.write(0);
    delay(TURN_TIME);
    myservo.write(90);
  }
  if (angle < 0){
    TURN_TIME = angle * 4.2 * -1;
    myservo.write(180);
    delay(TURN_TIME);
    myservo.write(90);
  }  
}

/* 
    This code should be pasted within the files where this function is needed.
    This function will not create any code conflicts.
    
    The function call is similar to printf: ardprintf("Test %d %s", 25, "string");

    To print the '%' character, use '%%'

    This code was first posted on http://arduino.stackexchange.com/a/201
*/

#ifndef ARDPRINTF
#define ARDPRINTF
#define ARDBUFFER 16 //Buffer for storing intermediate strings. Performance may vary depending on size.
#include <stdarg.h>
#include <Arduino.h> //To allow function to run from any file in a project

int ardprintf(char *str, ...) //Variadic Function
{
  int i, count=0, j=0, flag=0;
  char temp[ARDBUFFER+1];
  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++; //Evaluate number of arguments required to be printed
  
  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++) //Iterate over formatting string
  {
    if(str[i]=='%')
    {
      //Clear buffer
      temp[j] = '\0'; 
      Serial.print(temp);
      j=0;
      temp[0] = '\0';
      
      //Process argument
      switch(str[++i])
      {
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      };
    }
    else 
    {
      //Add to buffer
      temp[j] = str[i];
      j = (j+1)%ARDBUFFER;
      if(j==0)  //If buffer is full, empty buffer.
      {
        temp[ARDBUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  };
  
  Serial.println(); //Print trailing newline
  return count + 1; //Return number of arguments detected
}

#undef ARDBUFFER
#endif

void loop(){
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(500);
  //ardprintf("B%d%s", sensorValue, "E");
  //delay(500);
  
  if (sensorValue < 50){
    magnetPasses++;
    //ardprintf("B%d%s", magnetPasses, "E");
    //delay(100);
  }
  
  if (magnetPasses > calibrate){
    Serial.println("B1E");
    magnetPasses = 0;
  }
  
  if (Serial.available() > 0){
    i = Serial.parseInt();
    rotateServo(i);
  }  
}
