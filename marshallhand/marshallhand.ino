// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo thumb;
Servo pinky;
Servo middle;
Servo ring;
Servo fore;  // create servo object to control a servo 
 
  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
int finger1 = 8;
int finger2 = 12;
int finger3 = 10;
int finger4 = 11;
int finger5 = 9;
void setup() 
{ 
  thumb.attach(12);
  pinky.attach(11);
  middle.attach(10);
  ring.attach(9);
  fore.attach(8);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  for(int pos = 180; pos>=90; pos-=1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    thumb.write(pos);              // tell servo to go to position in variable 'pos' 
    fore.write(pos);
    middle.write(pos);
    ring.write(pos);
    pinky.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  
  delay(1000);
  for(int pos = 90; pos < 180; pos += 1)
   {
    thumb.write(pos);              // tell servo to go to position in variable 'pos' 
    fore.write(pos);
    middle.write(pos);
    ring.write(pos);
    pinky.write(pos);
    delay(15);
   }
  while(true)
    {
    val = analogRead(finger1);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    thumb.write(val);  
    val = analogRead(finger2);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    pinky.write(val);                  // sets the servo position according to the scaled value 
    val = analogRead(finger3);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    middle.write(val);
    val = analogRead(finger4);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    ring.write(val);
    val = analogRead(finger5);            // reads the value of the potentiometer (value between 0 and 1023) 
    val = map(val, 0, 1023, 1, 179);     // scale it to use it with the servo (value between 0 and 180) 
    fore.write(val);
    delay(15);
    }
} 
