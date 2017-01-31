// water chiller hardware test

// input buttons, they are digital inputs that are active LOW when the buttons are pressed
#define BUTTON_ON  5 //(chip pin 11)
#define BUTTON_OFF 6 //(chip pin 12)

// led indicator
#define STATUS_LED 13 //(chip pin 19)

// chiller control
#define CHILLER_CONTROL 3  // chip pin 5

// photocell analog input. The value is higher the more light there is
#define PHOTOCELL  1

// thermistor analalog input. The value goes down as the temperature goes up
#define THERMISTOR 0



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Water chiller hardware test\n");

  // set buttons as inputs with pullups
  pinMode(BUTTON_ON, INPUT_PULLUP);
  pinMode(BUTTON_OFF, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);
  
  digitalWrite(BUTTON_ON, HIGH);
  digitalWrite(BUTTON_OFF, HIGH);

  // turn off led
  digitalWrite(STATUS_LED, 0);  
  
  // set chiller control as an output with initial state of off
  digitalWrite(CHILLER_CONTROL, LOW);
  pinMode(CHILLER_CONTROL, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly: 

  int button_on_value = digitalRead(BUTTON_ON);
  int button_off_value = digitalRead(BUTTON_OFF);
  
  if (button_on_value == 0) {
    digitalWrite(STATUS_LED, HIGH);

    // turn on chiller
    //digitalWrite(CHILLER_CONTROL, HIGH); 
    analogWrite(CHILLER_CONTROL, 64); 
  }
  else if (button_off_value == 0) {
    digitalWrite(STATUS_LED, LOW);  

    // turn off chiller
    //digitalWrite(CHILLER_CONTROL, LOW); 
    analogWrite(CHILLER_CONTROL, 0); 
  }

  Serial.print(button_on_value);
  Serial.print("   ");
  Serial.print(button_off_value);
  Serial.print("   ");

  // read the photocell
  int photocell_value = analogRead(PHOTOCELL);
  
  Serial.print(photocell_value);
  Serial.print("   ");

  float temperature = ReadTemperature();  
  Serial.print(temperature);
  Serial.println(" *F");


  delay(10);
}


// read the temperature from the thermistor
// definitions for thermistor
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3984;  // this is for the NTCALUG03A103H that mount with a lug
// the value of the resistor connecting the thermistor to ground
#define SERIESRESISTOR 10000
 
// returns temperature in F 
float ReadTemperature() {
  int samples[NUMSAMPLES];
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTOR);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  //Serial.print("Average analog reading "); 
  //Serial.println(average);
 
  // convert the value to resistance
  float thermistor_resistance = 1023 / average - 1;
  thermistor_resistance = SERIESRESISTOR / thermistor_resistance;
  //Serial.print("Thermistor resistance "); 
  //Serial.println(thermistor_resistance);
 
  float temperature;
  temperature = thermistor_resistance / THERMISTORNOMINAL;     // (R/Ro)
  temperature = log(temperature);                  // ln(R/Ro)
  temperature /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                 // Invert
  temperature -= 273.15;                         // convert to C
 
  //Serial.print("Temperature "); 
  //Serial.print(temperature);
  //Serial.println(" *C");

  // brian: convert to F - I don't think in C
  temperature = (temperature * 9 / 5) + 32;
  
  return temperature;
}
