  #define GRAPH_CHARS 80
  char graph_line[81];
  #include <NewPing.h>
  NewPing sensor (13,12);
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  memset(graph_line, 0, GRAPH_CHARS+1);
}
void loop() {
  // put your main code here, to run repeatedly: 
  float distance = ReadDistance();
  //Serial.print(distance,1);
  //Serial.println(" in");
  if(distance > 100)
    distance =100;
  int graph_val = map(distance, 0, 100, 0, 80);
   int i = 0;
  for (i = 0; i < graph_val; ++i)
    graph_line[i] = 'X';
  graph_line[i] = 0;
  Serial.println(graph_line);
  delay(50);
}
float ReadDistance()
{
  // get ping time in micro-seconds 
  unsigned int uS = sensor.ping();
  // convert time to distance in inches
  float distance = (float)uS / (float)US_ROUNDTRIP_IN;
  return distance;
}
