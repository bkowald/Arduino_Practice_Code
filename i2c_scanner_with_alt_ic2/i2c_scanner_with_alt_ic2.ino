/* scan using alternative i2c library that supports repeated start and does not hang
http://dsscircuits.com/articles/arduino-i2c-master-library.html
*/

#include <I2C.h>

void setup()
{
  I2c.begin();
  Serial.begin(9600);
  Serial.write("Welcome to the scanner\n");
}

void loop()
{
  // note: timeout is built in to scan function
  I2c.scan();
  while(true);  // halt
}

