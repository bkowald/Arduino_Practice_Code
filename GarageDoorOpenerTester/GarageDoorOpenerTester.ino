/*
  Garage door opener tester
  
  This monitors the relay contact of the garage door opener project and counts the number of times its activated.
  
  The purpose is to detect inadverdant triggering.
 
 Connections:
   LED on pin 13 blinks to indicate how many times its been activated
   Digital input 2 connected to the garage door opener relay with the other contact connected to ground (active low)

*/

// constants won't change. They're used here to 
// set pin numbers:
#define BUTTON_PIN  2        // the number of the pushbutton pin or relay from garage door opener
#define LED_PIN    13        // the number of the LED pin

int buttonState = 0;         // track if the relay (button) is currently on or off
int lastButtonState = 0;     // track if the relay (button) is currently on or off

int numberOfActivations = 0;    // count how many times the relay activates

// track when to blink the led
long previousMillis = 0;
long interval = 2000;  

// debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // mili-seconds the debounce time; increase if the output flickers. Garage door fires for one second, so this can be nice and long
int lastDebounceState = 0;  // last state of button for debouncing

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);      
  
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT_PULLUP);     

  lastButtonState = digitalRead(BUTTON_PIN);  // initialize the first state of the button to be able to detect a change
  lastDebounceState = buttonState;
}


void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  //Serial.println(buttonState);

  // check if the pushbutton changed for debounce
  if (buttonState != lastDebounceState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 

  // remember current value for next debounce check
  lastDebounceState = buttonState;
  
  // check if debounce timer reached (button has not changed for long enough time)
  if ((millis() - lastDebounceTime) > debounceDelay) {

    //Serial.println("Debounce delay reached");

    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
    
      // if low, count an activation
      if (buttonState == LOW) {
          ++numberOfActivations;
          Serial.println("We have activation");
      }
    }
  }  
 
  // check if its time to flash the number of activations
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    DisplayActivationCount();  
    previousMillis = millis();  // start the timer over after the display delay 
  }
}

// blink the led to indicate the number of activations
void DisplayActivationCount() {
  int i;
  for (i = 0; i < numberOfActivations; ++i) {
    digitalWrite(LED_PIN, HIGH);  
    delay(200);
    digitalWrite(LED_PIN, LOW);  
    delay(200);
  }     
}
