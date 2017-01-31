// Useless Machine
// By Brian Kowald

/* Connect a servo to Pin D2 (chip pin 4)
   Connect a switch input to D3 (chip pin 5)
*/

#include <Servo.h> 

// inputs and outputs
#define SERVO_PIN 2
#define SWITCH_INPUT 3    // reads LOW when user has flipped switch and servo needs to push it. Reads high once servo has moved switch

// servo positions
// the "home" position. This is the position the servo moves to once it has pushed the switch
#define SERVO_HOME 0    
// the position the servo moves to to push the switch. Don't oveerdrive it
#define SERVO_PUSH_SWITCH 105

// create a servo object
Servo myservo; 

void setup() 
{ 
  myservo.attach(2);  // D2 or chip pin 4
  
  // set switch as an input
  pinMode(SWITCH_INPUT, INPUT);
  digitalWrite(SWITCH_INPUT, HIGH);  // turn on pullup resistor so we won't have to add one. The pullup is around 20K
} 

void loop() 
{ 
  // check if the switch needs to be pushed by the servo
  if (digitalRead(SWITCH_INPUT) == LOW) {
    // the user has flipped the switch. Push it back "off"
    delay(200);
    myservo.write(SERVO_PUSH_SWITCH);
    delay(100);
  }
  else {
    // switch has been pushed by the servo, so move the servo to the "home" position
    myservo.write(SERVO_HOME);
  }
  
  // delay some to let the servo move
  delay(15);                      
} 

   
   
