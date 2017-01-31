
// read an analog port and control the brightness of an led

#define LED1 13
#define LED2 3

void setup()  { 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
} 

void loop()  { 

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(500);
  
}



