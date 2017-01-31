// Continuous server as a motor test
// uses the serial port for control  1-slower 2-faster 

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 90;    // neurtral, motor or server should not move

void setup() 
{ 
  // note: can specify pulse widths as second and third parameters for things like speed controllser talon speed controller. remove for defaults
  myservo.attach(2);  // D2 or chip pin 4
  
  // motor drive server connected to a TALON
  //myservo.attach(3, 1000, 2000); // TALON  // widths are in micro-seconds 
  
  
  Serial.begin(9600);
  Serial.write("Welcome\nPress 1 for slower or 2 for faster. Press 3 to turn motor off.");
  Serial.println(myservo.read());

  myservo.write(pos);

  Serial.println(myservo.read());

} 

void loop() 
{ 
  // see if a character is available
  if (Serial.available() > 0) {
    int c = Serial.read();
    if (c == '1') {
      if (pos > 0)
        pos -= 1;  
    }
    else if (c == '2') {
      if (pos < 180)
        pos += 1;
    }
    else if (c == '3') {
      pos = 90;  // turn off
    }

    myservo.write(pos);

    // display the value. Note: use print and not write. write is for binary data   
    Serial.print("Position: ");
    Serial.println(pos, DEC);

    delay(15);
  }


} 

