
// calibrate a speed controller (victor, jaguar, talon)

// this goes from off (90) to full forward (180), to full reverse (0) and then back to 90

// connect PWM to the servo on D3

#define SPEED_CONTROLLER 3

#include <Servo.h> 

Servo myservo;


void setup() {   
  // the defaults min and max pulse widths are 544us and 2400us. that's out of the talon range of 1000-2000. Its OK for the Jaguare which is 500 to 2500 us.
  // not sure what the victor requires
  // my old Futaba servo needs 300 or even a little less to go full range for 0 degrees
  //myservo.attach(SPEED_CONTROLLER);    // default min and max widths of 544 and 2400
  myservo.attach(SPEED_CONTROLLER, 1000, 2000); // TALON  // widths are in micro-seconds 
  
  myservo.write(90);    // off
  Serial.begin(9600);
  
  
  
}

void loop() {
  Serial.println("Welcome to Speed Controller Calibration.\nPress and HOLD the button labeled \"CAL\" with a paper clip.\nThe LED should begin to blink red/green.\nPress any key when its blinking");

  WaitKey();

  Serial.println("Setting Full Forward. Press any key to switch to full reverse. Keep holding CAL button!");
  myservo.write(180);
 
  WaitKey();
   
  Serial.println("Setting Full Reverse. Press any key to for neutral / off. Don't let go of the CAL button yet!");
  myservo.write(0);
   
  WaitKey();
  
  Serial.println("Setting to neutral. You may now let go of the calibration button.\nIf the calibration was successful, the LED will blink green several times.\nPress any key to repeat the calibration cycle.");
  myservo.write(90);
  
  WaitKey();
  
}

// wait for any key to be received. returns the character received
int WaitKey() {
  while (Serial.available() == 0) {
    ;
  }
  return Serial.read();
}
