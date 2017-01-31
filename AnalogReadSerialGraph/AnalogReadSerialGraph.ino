
// read an analog input and print a scaled number of characters on each line

#define GRAPH_CHARS 170
char graph_line[GRAPH_CHARS + 1];  // need blank ending 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  memset(graph_line, 0, GRAPH_CHARS+1);
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  // read the analot port
  int sensorValue = analogRead(A0); 
  int graph_val = map(sensorValue, 0, 1023, 0, GRAPH_CHARS);
  
  int i = 0;
  for (i = 0; i < graph_val; ++i)
    graph_line[i] = 'X';
  graph_line[i] = 0;  // add terminating 0  
  
  Serial.println(graph_line);
  delay(5);  
 
}
