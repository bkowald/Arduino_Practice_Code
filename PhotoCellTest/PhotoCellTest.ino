/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to an analog input
Then connect one end of a 10K resistor from Analog 0 to ground 
For more information see http://learn.adafruit.com/photocells 
*/
 
int photocellPin = 2;     // the cell and 10K pulldown are connected to this analog input

// create a serial bar graph of the value
#define GRAPH_CHARS 170
char graph_line[GRAPH_CHARS + 1];  // need blank ending 0

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(115200);   
  memset(graph_line, 0, GRAPH_CHARS+1);
}
 
void loop(void) {
  int photocellReading = analogRead(photocellPin);  
 
  //Serial.print("Analog reading = ");
  //Serial.println(photocellReading);     // the raw analog reading

  // display as a bar graph
  int graph_val = map(photocellReading, 0, 1023, 0, GRAPH_CHARS);
  
  int i = 0;
  for (i = 0; i < graph_val; ++i)
    graph_line[i] = 'X';
  graph_line[i] = 0;  // add terminating 0  
  
  Serial.println(graph_line);
  
  delay(5);
}


