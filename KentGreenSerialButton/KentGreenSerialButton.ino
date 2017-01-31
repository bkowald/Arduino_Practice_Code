// Kent Green's serial button 
//Three loops in a row (no loops in a loop) ((while)&(for++)&(for+4)

//Serial output, Serial input, 

const int BUTTON = 7; // the pin the BUTTON is connected to
int i = 0;
int j = 0;
 
const int led = 13;

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and
                      // receive at 9600 baud
  pinMode(BUTTON, INPUT);
  pinMode(led, OUTPUT);
}


 void loop()
{

    int val = (digitalRead(BUTTON));

    digitalWrite(led, val);
    
     while(val==HIGH)
  	{
 	if ( Serial.available()) // Check to see if at least one
                           	 // character is available
      		{
     		 blink();
      		 //break;
    		}
  	}

    for(int i=0; i < 10; i++)
  	{
	Serial.println("the variable i is now = to ");
	Serial.println(i);
  	}

    for(int j=4; j < 36; j+=4)
  	{
	Serial.println("the variable j is now = to ");
	Serial.println(j);
  	}

}// Arduino loop is closed

void blink()
{
      char ch = Serial.read();
      Serial.print(ch);
      Serial.println(" was the character entered on keyboard");
}

      

