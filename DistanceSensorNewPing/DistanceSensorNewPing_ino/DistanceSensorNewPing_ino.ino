// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h> 

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo servo;  // create servo object to control a servo 


void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  servo.attach(2);    // does this interfere with the ping?
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).

  float distance_in_cm = (float)uS / (float)US_ROUNDTRIP_CM; // Convert ping time to distance in cm and print result (0 = outside set distance range)
  float distance_in_in = (float)uS / (float)US_ROUNDTRIP_IN;

  Serial.print("Ping: ");
  Serial.print(distance_in_cm, 1); 
  Serial.print("cm  ");

  Serial.print(distance_in_in, 1);  
  Serial.println("in");

}
