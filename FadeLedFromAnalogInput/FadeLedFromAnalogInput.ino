
// read an analog port and control the brightness of an led

int ledPin = 3;    // LED connected to digital pin 3 AtMega328 pin 5

void setup()  { 
 Serial.begin(9600);
} 

void loop()  { 

  // read analog port. Its value will be 0-1023  
  int sensorValue = analogRead(A0);

  // map it to a range of 0-255 for the led brightness control
  // the input never gets to 1023, so output never gets to 255
  // see if map handles it if it goes over
  if (sensorValue > 1010)
    sensorValue = 1010;
  int ledValue = map(sensorValue, 0, 1010, 0, 255);
  
  Serial.println(ledValue);

  // sets the value (range from 0 to 255):
  analogWrite(ledPin, ledValue);         
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}



