// which analog pin to connect
#define THERMISTORPIN A1
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3977;  // the thermistor I got from digi key is 3977. Adafruit's example used one with 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 9880  // measured with meter for particular resistor     
 
int samples[NUMSAMPLES];
 
void setup(void) {
  Serial.begin(9600);
  // brian: not going to have a separate analog reference on the "real" board"
  //analogReference(EXTERNAL);
}
 
void loop(void) {
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  Serial.print("Average analog reading "); 
  Serial.println(average);
 
  // convert the value to resistance
  float thermistor_resistance = 1023 / average - 1;
  thermistor_resistance = SERIESRESISTOR / thermistor_resistance;
  Serial.print("Thermistor resistance "); 
  Serial.println(thermistor_resistance);
 
  float temperature;
  temperature = thermistor_resistance / THERMISTORNOMINAL;     // (R/Ro)
  temperature = log(temperature);                  // ln(R/Ro)
  temperature /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                 // Invert
  temperature -= 273.15;                         // convert to C
 
  Serial.print("Temperature "); 
  //Serial.print(temperature);
  //Serial.println(" *C");

  // brian: convert to F - I don't think in C
  temperature = (temperature * 9 / 5) + 32;
  Serial.print(temperature);
  Serial.println(" *F");
 
  delay(1000);
}


