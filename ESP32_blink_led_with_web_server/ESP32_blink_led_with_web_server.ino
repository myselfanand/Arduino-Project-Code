#include <WiFi.h>
#include <WiFiClient.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "JCBRO";
char pass[] = "jcbro@321";
WiFiServer server(80);

String header;

String LED_ONE_STATE = "off";

const int pin= 2;

void setup() { 
  Serial.begin(9600);
  pinMode(pin, OUTPUT); 
  pinMode(pin, LOW);

  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("it'll take a moment to connect with wifi \n");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop(){
WiFiClient client = server.available(); 
if (client) { 
Serial.println("New Client is requesting web page"); 
String current_data_line = ""; 
while (client.connected()) { 
if (client.available()) { 
char new_byte = client.read(); 
Serial.write(new_byte); 
header += new_byte;
if (new_byte == '\n') { 
         
if (current_data_line.length() == 0) 
{
            
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

  if (header.indexOf("LED0=ON") != -1) 
{
Serial.println("pin LED is ON");
LED_ONE_STATE = "on";
digitalWrite(pin, HIGH);
} 
if (header.indexOf("LED0=OFF") != -1) 
{
Serial.println("pin LED is OFF");
LED_ONE_STATE = "off";
digitalWrite(pin, LOW);
} 
 
// Web Page Heading
client.println("</style></head>");
client.println("<body><center><h1>ESP32 Web server LED controlling example</h1></center>");
client.println("<center><h2>Web Server Example Microcontrollerslab.com</h2></center>" );
client.println("<center><h2>Press on button to turn on led and off button to turn off LED</h3></center>");
client.println("<form><center>");
client.println("<p> LED one is " + LED_ONE_STATE + "</p>");
// If the PIN_NUMBER_22State is off, it displays the ON button 
client.println("<center> <button class=\"button\" name=\"LED0\" value=\"ON\" type=\"submit\">LED0 ON</button>") ;
client.println("<button class=\"button\" name=\"LED0\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br>");
client.println("</center></form></body></html>");
client.println();
break;
} 
else 
{ 
current_data_line = "";
}
} 
else if (new_byte != '\r') 
{ 
current_data_line += new_byte; 
}
}
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
