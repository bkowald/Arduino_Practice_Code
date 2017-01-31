/*
  FRC motor tester

  Created 3-14-2015. The ultimate PI day  3.14.15.92653

 */
#include <Servo.h> 
// digital pin 2 has a pushbutton attached to it. Give it a name:
#define BUTTON_1 3
#define BUTTON_2 4
#define BUTTON_3 5
// analog input for speed control
#define SPEEDIN 0
bool lastDerect = true;

Servo driveServo;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  
  driveServo.attach(2, 1000, 2000);
  driveServo.write(90);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int button1State = digitalRead(BUTTON_1);
 // Serial.print(button1State);
  
  int button2State = digitalRead(BUTTON_2);
 // Serial.print(button2State);
  
  int button3State = digitalRead(BUTTON_3);
 // Serial.print(button3State);
  
  int speedState = analogRead(SPEEDIN);
 // Serial.println(speedState);
  
  speedState = map(speedState, 0, 1023, 0, 90);
  
  int servoOut = 90;
  if (button3State == 0)
   {
     if (lastDerect == true)
     {
       servoOut = (90 + speedState);
     }
     else
     {
       servoOut = (90 - speedState);
     }
   }
    else if (button1State == 0)
    {
      servoOut = (90 + speedState);
      lastDerect = true;
    }
   else if (button2State == 0)
   {
     servoOut = (90 - speedState);
     lastDerect = false;
   }
  Serial.println(servoOut);
  driveServo.write(servoOut); 
  delay(1);        // delay in between reads for stability
}



