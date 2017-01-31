
int led =13;
int button =3;
int val;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}
  
void loop() {
  // put your main code here, to run repeatedly: 
 val = digitalRead(button);
if(val == LOW)
   digitalWrite(led, LOW);
else
   digitalWrite(led, HIGH);
}
