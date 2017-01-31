#include <CapacitiveSensor.h>
#include <Servo.h> 

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_3 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 3, pin 3 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

#define THRESHOLD 100

#define LED 13

Servo servo;

void setup()                    
{
   //cs_4_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   pinMode(LED, OUTPUT);
   servo.attach(2);  // D2 or chip pin 4
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_3.capacitiveSensor(30);
    //long total2 =  cs_4_6.capacitiveSensor(30);
    //long total3 =  cs_4_8.capacitiveSensor(30);

    digitalWrite(LED, total1 > THRESHOLD);

    servo.write(total1 > THRESHOLD ? 110 : 50);

    Serial.print(millis()   - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(total1);                  // print sensor output 1

    Serial.println(""); 
    
    /*
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3
    */
    
    delay(10);                             // arbitrary delay to limit data to serial port 
}
