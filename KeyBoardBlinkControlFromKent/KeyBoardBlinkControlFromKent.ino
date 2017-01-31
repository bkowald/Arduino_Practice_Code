//Digital input from Button, LED Output, keyboard (serial) inputs,
//Serial output to screen, while condition, subroutine and case structures

const int LED = 13; // the pin the LED is connected to
const int BUTTON = 7; // the pin the BUTTON is connected to
int val = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and 
                      // receive at 9600 baud
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  val = (digitalRead(BUTTON));
  if (val == HIGH)
  { 
    if ( Serial.available()) // Check to see if at least one character is available
    {
      char ch = Serial.read();
      switch(ch)
      {
      case '1':
        blink();
        break;
      case '2':
        blink();
        blink();
        break;
      case '+':
        digitalWrite(LED,HIGH);
        break;
      case '-':
        digitalWrite(LED,LOW);
        break;
      default :
        Serial.print(ch);
        Serial.println(" was received but not expected");
        break;
       }
     }
   }
}

void blink()
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}
