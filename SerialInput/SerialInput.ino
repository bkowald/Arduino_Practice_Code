// this controls LEDS based on keyboard input

#define LED1 13
#define LED2 3

void setup() {
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
  Serial.write("Welcome\nPress 1 for LED1 or 2 for LED2. Press 3 to turn both off.");
}

void loop() {
  // see if a character is available
  if (Serial.available() > 0) {
    int c = Serial.read();
    if (c == '1') {
        digitalWrite(LED1, HIGH);
        Serial.write("One on\n");
    }
    else if (c == '2') {
        digitalWrite(LED2, HIGH);
        Serial.write("Two on\n");
    }
    else if (c == '3') {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      Serial.write("Both off\n");
   }
  }
  
  delay(10);
}
