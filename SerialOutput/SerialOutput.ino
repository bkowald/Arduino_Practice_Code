void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("Welcome\n");
}

void loop() {
  // put your main code here, to run repeatedly: 
  static int count = 0;
  
  Serial.write("hello for the ");
  Serial.print(count++, DEC);
  Serial.write(" th time\n");
  delay(1000);
}
