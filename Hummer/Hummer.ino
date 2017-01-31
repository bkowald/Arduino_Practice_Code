
// hummer robotics project

#include <Servo.h> 
#include <NewPing.h>

// steering values for servo
#define STEER_STRAIGHT  100
#define STEER_FULL_RIGHT 71
#define STEER_FULL_LEFT 138
#define STEER_SLIGHT_RIGHT 85
#define STEER_SLIGHT_LEFT 115

// distance to maintain from the wall
#define MAINTAIN_DIST_MIN 11.5
#define MAINTAIN_DIST_MAX 12.5
#define MAX_DISTANCE_IN_CM 200        // in centimeters. The sensor library requires it in centimeters

// sttering control
Servo steerServo;  // create servo object to control a servo 

// motor control
Servo driveServo;

#define DRIVE_STOP 90
#define DRIVE_FORWARD_SLOW 105

// distance sensors
#define SENSOR_LEFT 0  // index in sensor array

// array of sensors. Set number of sensors when adding
#define NUMBER_OF_SENSORS 1
NewPing sensors[NUMBER_OF_SENSORS] = {
  NewPing(13, 12, MAX_DISTANCE_IN_CM)  // left. NewPing setup. Numbers are trigger pin, echo pin, and maximum distance IN CENTIMETERS
};

void setup() {
  // put your setup code here, to run once:
  
  // steering server
  steerServo.attach(2);  // D2 or chip pin 4
  steerServo.write(STEER_STRAIGHT);

  // motor drive server connected to a TALON
  driveServo.attach(3, 1000, 2000); // TALON  // widths are in micro-seconds 
  driveServo.write(DRIVE_STOP);   
  
  Serial.begin (9600);
}

void loop() {

  delay(100);
  
  // read the distance from the left sensor
  float distance = ReadDistance(SENSOR_LEFT);
  
  Serial.print(distance,1);
  Serial.println(" in");  
   
  if (distance == 0) { // out of range
    driveServo.write(DRIVE_STOP);
  }
  else {
    // distance is in range, so turn on drive motor
    driveServo.write(DRIVE_FORWARD_SLOW); 
    
    if (distance < MAINTAIN_DIST_MIN) {
        // steer right
        steerServo.write(STEER_SLIGHT_RIGHT);
    }
    else if (distance > MAINTAIN_DIST_MAX) {
        // steer left
        steerServo.write(STEER_SLIGHT_LEFT);
    }
    else {
      // steer straight
      steerServo.write(STEER_STRAIGHT);
    }
  }
  
  
  
}

// read the distance sensor. Specify index in sensor array
// returns: distance in INCHES. 0 means out of range
float ReadDistance(int sensor_index)
{
  // get ping time in micro-seconds 
  unsigned int uS = sensors[sensor_index].ping();
  
  // convert time to distance in inches
  float distance = (float)uS / (float)US_ROUNDTRIP_IN;
  return distance;
}
