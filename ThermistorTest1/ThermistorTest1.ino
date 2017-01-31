// the value of the 'other' resistor
#define SERIESRESISTOR 9888    
 
// What pin to connect the sensor to
#define THERMISTORPIN A1
 
void setup(void) {
  Serial.begin(9600);
}
 
void loop(void) {
  float reading;
 
  reading = analogRead(THERMISTORPIN);
 
  Serial.print("Analog reading "); 
  Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;
  Serial.print("Thermistor resistance "); 
  Serial.println(reading);
 
  delay(1000);
}

