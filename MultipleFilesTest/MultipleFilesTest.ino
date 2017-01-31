
#include "file2.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 

  // call a function in a different file
  int v = foo();
  
  Serial.write("hello for the ");
  Serial.print(v, DEC);
  Serial.write(" th time\n");
  delay(1000);
 
  
}
