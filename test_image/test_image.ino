#include <WiFi.h> 
#include <WebServer.h>

const char* ssid = "JCBRO"; 
const char* password = "jcbro@321";

WiFiServer server(80);

String header;

void setup() 
{
Serial.begin(9600);
Serial.print("Connecting to Wifi Network");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Successfully connected to WiFi.");
Serial.println("IP address of ESP32 is : ");
Serial.println(WiFi.localIP());
server.begin();
Serial.println("Server started");
}

void loop() {
WiFiClient client = server.available();
if (client) 
{ 
Serial.println("Web Client connected ");
String page = client.readStringUntil('\r');

 client.println("<!DOCTYPE html><html>");
 client.println("<HEAD><TITLE>My first web page</TITLE></HEAD>");
 client.println("<BODY Style=background-color:YELLOW; font-size:150%><center>");
 client.println("<h style=color:RED;font-size:200%>Welcome to our Dynamic Web Page &#128515;</h><center> <br>");
 client.println("<img src=\"https://images.unsplash.com/photo-1565206595640-6cfd90e0ae09?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxzZWFyY2h8MTd8fGVudmlyb25tZW50fGVufDB8fDB8fA%3D%3D&auto=format&fit=crop&w=700&q=60\" alt=\"download\" width=\"500\" height=\"500;\"> <br>");
 client.println("<h2 style=color:RED> Thank You so Much ! &#10084 </h2>");
 client.println("</BODY></HTML>");
}
}
