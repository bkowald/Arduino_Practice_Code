
// test driving a fet

// reads an analog input to control a fet

#define KNOB_INPUT 0
#define FET_DRIVE 3

void setup() {
  // put your setup code here, to run once:
  pinMode(KNOB_INPUT, INPUT);
  pinMode(FET_DRIVE, OUTPUT);
  Serial.begin(19200); 
}

void loop() {
  
  // read the analot port
  int sensorValue = analogRead(KNOB_INPUT); 
  
  int fet_drive = map(sensorValue, 0, 1023, 0, 255); 
  
  analogWrite(FET_DRIVE, fet_drive);
  
  Serial.println(fet_drive);
  delay(5);  
 
}
