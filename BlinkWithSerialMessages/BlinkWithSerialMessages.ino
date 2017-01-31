/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int loop_counter = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  Serial.begin(9600);	
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("led on");
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  
  Serial.println("led off");
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second
  
  ++loop_counter;
  Serial.print("Loop counter = ");
  Serial.println(loop_counter);

}

