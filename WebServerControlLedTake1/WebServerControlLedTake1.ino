/*
  Brian: modified with my ip
  
  Note: don't use D13, thats in use (SPI CLK)

 Allows you to turn on and off an LED by entering different urls.
 
 To turn it on:
 http://your-IP-address/?1
 
 To turn it off:
 http://your-IP-address/?2
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Connect an LED to pin D13 and put it in series with a 220 ohm resistor to ground
 
 Based almost entirely upon Web Server by Tom Igoe and David Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

boolean incoming = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
IPAddress ip(192,168,1,177);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

#define LED_PIN 2

void setup()
{
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //int i = c;
        //Serial.print("(");
        //Serial.print(i);
        //Serial.print(")");

        //reads URL string from ? to first blank space
        if (incoming && c == ' '){ 
          incoming = 0;
        }
        if(c == '?'){ 
          incoming = 1; 
        }
        
        //Checks for the URL string ?1 or ?2
        if (incoming == 1){
          //Serial.println(c);
          if(c == '1'){
            Serial.println("ON");
            digitalWrite(LED_PIN, HIGH);
          }
          if(c == '2'){
            Serial.println("OFF");
            digitalWrite(LED_PIN, LOW);
          }
        }

        // Brian: added this to display a webpage
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
           Serial.println("receive complete"); 
            // send a standard web page
           SendWebPage(client); 
           currentLineIsBlank = true; 
           break; 
        } 

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

// send web page
void SendWebPage(EthernetClient client)
{
   client.println("HTTP/1.1 200 OK"); 
   client.println("Content-Type: text/html"); 
   client.println("Connnection: close"); 
   client.println(); 
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   
   client.println("<head>");
   client.println("<title>LED Control</title>");
   client.println("</head>");

   client.println("<body>");
   
   client.println("Brians Led Control<br/>");
   
   // read the LED and display its status
   if (digitalRead(LED_PIN) == HIGH)
     client.println("LED is ON<br>"); 
   else  
     client.println("LED is OFF<br>"); 

   // on and off buttons    
   client.println("<button onclick=\"javascript:window.location.href='X?1';\">On</button>");
   client.println("<button onclick=\"javascript:window.location.href='X?2';\">Off</button>");

   client.println(""); 

   client.println("</body>");
   client.println("</html>");
}
