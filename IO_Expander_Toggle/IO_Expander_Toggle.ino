#include <Wire.h>
#include "Adafruit_MCP23017.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)

// Output #0 is on pin 21 so connect an LED or whatever from that to ground
// Brian - added Output#1

Adafruit_MCP23017 mcp;
  
void setup() {  
  Serial.begin(9600);
  Serial.println("hello");

  mcp.begin();      // use default address 0
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);

  // brian: added input on pin 15 (port b, pin 7)
  mcp.pinMode(15, INPUT);
  mcp.pullUp(15, HIGH);  // turn on a 100K pullup internally
  
  Serial.println("pin setup complete");
}


// flip the pin #0 up and down

void loop() {
  delay(500);
  Serial.println("Hi");

  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(1, LOW);

  delay(500);
  Serial.println("Low");

  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, HIGH);
  
  // Brian: read the input
  Serial.print("Input 15 is ");
  Serial.println(mcp.digitalRead(15) == 0 ? "Low" : "High");
  
}
