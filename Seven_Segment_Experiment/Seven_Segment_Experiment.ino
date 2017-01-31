/*************************************************** 
  This is a test for the Adafruit seven segment dislay controlled by I2C

  For example:
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

****************************************************/
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment seven_segment;

void setup() {
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");

  seven_segment.begin(0x70);  // default address without modifying the backpack board
}

void loop() {
  
  // methods: control: setBrightness(0-15) 15 is brightest, blinRate(0-3), clear()
  // write numbers: print, println
  // write to a digit: writeDigitNum(location, number, show_decimal=false). 0 is all the way to the left, 1 is second digit, 2 is the colons, 3 is third digit 4 is rightmost digit.
  // write a bitmask: writeDigitRaw(location,bitmask)  see below for bit to segment mapping
  // turn the colon on or off: seven_segment.drawColon()
  
  // note: always call writeDisplay() after updating display memory to send data to display

  seven_segment.setBrightness(10);    // 0-15
  
  // try to print a number thats too long
  seven_segment.print(10000, DEC);
  seven_segment.writeDisplay();
  delay(1000);

  seven_segment.clear();

  // try to print a 0
  seven_segment.print(0);  // this was fixed on 12-2-13
  //seven_segment.writeDigitNum(4, 0);  // this works
  seven_segment.writeDisplay();
  delay(1000);

  // but a 1 works
  seven_segment.print(1);
  //seven_segment.writeDigitNum(4, 0);
  seven_segment.writeDisplay();
  delay(1000);


  // print a hex number
  seven_segment.print(0xABCD, HEX);
  seven_segment.writeDisplay();
  delay(1000);

  // create a timer
  unsigned long total_seconds;
  unsigned long hours, minutes, seconds;
  unsigned long value_to_display;
  bool colon_on = false;  // used to toggle the colon
  
  seven_segment.clear();
  while(1) {
    total_seconds = millis() / 1000;  // convert to seconds
    seconds = total_seconds % 60;
    minutes = (total_seconds / 60) % 60;
    hours = total_seconds / 3600;  
    
    if (hours > 0) {
      // show hours and minutes
      value_to_display = hours * 100 + minutes;
    }
    else {
      // show minutes and seconds
      value_to_display = minutes * 100 + seconds;
    }

    // write to the display    
    seven_segment.print(value_to_display);
    colon_on = colon_on ? false : true;
    seven_segment.drawColon(colon_on);
    seven_segment.writeDisplay();
    
    delay(500);  // only showing seconds, so no need to update too frequently  
  }  // end infinite timer loop  

  seven_segment.clear();
  seven_segment.writeDisplay();
  
  // print a bitmask. these are the bit positions showing what segment they turn on. Note: bit 7 is the decimal point
  //      0   
  //   5     1
  //      6   
  //   4     2  
  //      3      7
  //
  // colon bitmask: bit0 is both dots of the colon
  /*
  uint8_t bitmask = 1;
  for (int i = 0; i < 8; ++i) {
    seven_segment.writeDigitRaw(0, bitmask);
    seven_segment.writeDisplay();
    Serial.println(bitmask, HEX);
    delay(500);
    bitmask = bitmask << 1;
  }
  delay(1000);
  */

  // print a floating point 
  /* this isnt working yet, still hacking on it!
  seven_segment.print(12.34);
  seven_segment.writeDisplay();
  delay(500);
  */

  seven_segment.blinkRate(0);
 
  // print with print/println
  for (uint16_t counter = 0; counter < 9999; counter++) {
    seven_segment.print(counter);
    seven_segment.writeDisplay();
    //delay(5);
  }

  // brian: countdown
  for (uint16_t counter = 9999; counter > 0; --counter) {
    seven_segment.print(counter);
    seven_segment.writeDisplay();
  }
 
  // blink all 0's. Must use writeDigitNum, otherwise, 0 is blanked out if its a leading digit
  seven_segment.writeDigitNum(0, 0, true);
  seven_segment.writeDigitNum(1, 0, true);
  seven_segment.writeDigitNum(3, 0, true);  // note: 2 is the position of the colon, so skip it
  seven_segment.writeDigitNum(4, 0, true);
  seven_segment.writeDisplay();
  seven_segment.blinkRate(1);
  delay(5000);
  seven_segment.blinkRate(0);

  // method #2 - draw each digit
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    seven_segment.writeDigitNum(0, (counter / 1000), drawDots);
    seven_segment.writeDigitNum(1, (counter / 100) % 10, drawDots);  
    seven_segment.drawColon(drawDots);
    seven_segment.writeDigitNum(3, (counter / 10) % 10, drawDots);
    seven_segment.writeDigitNum(4, counter % 10, drawDots);
   
    blinkcounter+=50;
    if (blinkcounter < 500) {
      drawDots = false;
    } else if (blinkcounter < 1000) {
      drawDots = true;
    } else {
      blinkcounter = 0;
    }
    seven_segment.writeDisplay();
    delay(10);
  }
}
