// water condender

// This controls a thermal chiller to maintain a temperature near, but abovr freezing so that water will condense on a metal panel
// Revisions:
// 8/17/2014  Ver 1
//            Manual on-off with button control plus an automatic mode. 
//            Indicator LED: 0-off 1-on 2-automatic

// input buttons, they are digital inputs that are active LOW when the buttons are pressed
// the on button is used to manually turn the chiller on if pressed quickly. If both are pressed at the same time, enter automatic mode
#define BUTTON_ON  5 //(chip pin 11)

// manuall turn the chiller off and enter manual mode
#define BUTTON_OFF 6 //(chip pin 12)

// led indicator
// off means the chiller is off and in manual mode, on means on in manual mode, blink means automatic mode
#define STATUS_LED 13 //(chip pin 19)

// chiller control. This turns on a FET when high
#define CHILLER_CONTROL 3  // chip pin 5

// photocell analog input. The value is higher the more light there is
#define PHOTOCELL  1

// thermistor analalog input. The value goes down as the temperature goes up
#define THERMISTOR 0

// the target temperature in Farenheit. It should be near freezing, but not below for max condensation to form. Set to higher to test
#define TARGET_TEMPERATURE 70.0

// the current mode: 0-manual 1-automatic
#define MODE_MANUAL 0
#define MODE_AUTOMATIC 1
int mode = 0;

// current state of chiller on/off. Track to print when state changes
int chiller_state = 0;

// the amount to drive the chiller. Range is 0-255
// this allows it to be driven with an analog value by using PWM. 255 = full on
#define CHILLER_TURN_ON_AMOUNT   64

int led_state = LOW;      // save the led state (on or off) so it can be toggled in atomatic mode
long previousMillis = 0;  // will store last time LED was toggle

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

  mode = MODE_AUTOMATIC;
  chiller_state = 0;  
}

void loop() {
  // main code here, runs repeatedly: 

  // if automatic mode, turn chiller on or off based on target temperature
  float temperature = ReadTemperature();  
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" *F");

  
  if (mode == MODE_AUTOMATIC) {
    if (temperature < TARGET_TEMPERATURE) {
      // too cold, turn off
      TurnOnChiller(0);
      // if state toggled, print a notification
      if (chiller_state == 1) {
        chiller_state = 0;
        Serial.println("Turned chiller off");
      }
    }
    else if (temperature > TARGET_TEMPERATURE){
      // too warn, turn on
      TurnOnChiller(1);
      // if state toggled, print a notification
      if (chiller_state == 1) {
        chiller_state = 1;
        Serial.println("Turned chiller ON");
      }
    }

    // toggle the LED to indicate automatic mode
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > 1000) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;   

      // if the LED is off turn it on and vice-versa:
      if (led_state == LOW)
        led_state = HIGH;
      else
        led_state = LOW;

      // set the LED with the ledState of the variable:
      digitalWrite(STATUS_LED, led_state);
    }  // end blink led timer has elasped
  }   // end automatic mode

  // read buttons. they are active LOW
  int button_on_value = digitalRead(BUTTON_ON);
  int button_off_value = digitalRead(BUTTON_OFF);
  
  if (button_on_value == 0 && button_off_value == 1) {    // only ON button is pressed
    // turn on chiller
    TurnOnChiller(1);
    chiller_state = 1;
   
    // enter manual mode
    mode = MODE_MANUAL;    
    digitalWrite(STATUS_LED, HIGH);
  }  // end on button was pressed
  else if (button_off_value == 0) {
    // turn off chiller
    TurnOnChiller(0);
    chiller_state = 0;

    // enter manual mode
    mode = MODE_MANUAL;    
    digitalWrite(STATUS_LED, LOW);  
  }

  // if both buttons are pressed at the same time, enter automatic mode
  if (button_on_value == 0 && button_off_value == 0) {
    Serial.println("Entering automatic mode");
    mode = MODE_AUTOMATIC;
    
    // loop and wait until BOTH buttons are released. Otherwise, if one button is released before the other, we would go back to manual mode
    do {
      button_on_value = digitalRead(BUTTON_ON);
      button_off_value = digitalRead(BUTTON_OFF);
    }
    while (button_on_value == 0 || button_off_value == 0);
  }


  // read the photocell. Ignore for now
  int photocell_value = analogRead(PHOTOCELL);
  //Serial.print(photocell_value);
  //Serial.print("   ");

  // delay some because there is not that much to do
  delay(10);
}

// turn chiller on or off
// specify 0 to turn off, or 1 to turn on
void TurnOnChiller(int on) {
    if (on == 1) {
      //digitalWrite(CHILLER_CONTROL, HIGH); 
      analogWrite(CHILLER_CONTROL, CHILLER_TURN_ON_AMOUNT); 
    }
    else {
      //digitalWrite(CHILLER_CONTROL, LOW); 
      analogWrite(CHILLER_CONTROL, 0); 
    }
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
