#include <Adafruit_MPL3115A2.h>
#include <WiFi.h> 
#include <Wire.h>
#include <WebServer.h>

const char* ssid = "JCBRO"; 
const char* password = "jcbro@321";

WiFiServer server(80);

String header;
Adafruit_MPL3115A2 baro;

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

while(!Serial);
  Serial.println("Adafruit_MPL3115A2 test!");

  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }

  // use to set sea level pressure for current location
  // this is needed for accurate altitude measurement
  // STD SLP = 1013.26 hPa
  baro.setSeaPressure(1013.26);
}

void loop() {
Serial.print("Temp = ");
Serial.print(baro.getTemperature());
Serial.println("°C");

Serial.print("Pressure = ");
Serial.print(baro.getPressure());
Serial.println(" Pa");


Serial.print("Altitude = ");
Serial.print(baro.getAltitude());
Serial.println(" meters");


Serial.println();
delay(500);
WiFiClient client = server.available();

if (client) 
{ 
Serial.println("Web Client connected ");
String page = client.readStringUntil('\r');

client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

client.print("<HTML><meta http-equiv=\"refresh\" content=\"2\">");
client.print("<body style=background-color:LemonChiffon; ALIGN=CENTER ><h1 style=color:RED;font-size:300%>Pressure Sensor Data Using ESP32</h1>");
client.print("<h2 style=color:PURPLE;font-size:200%> MPL3115A2 Barometric Sensor Data &#128071;  </h2>");

client.println("<p style=color:GREEN;font-size:160%>Temp=<span class=\"sensor\">");
client.println(baro.getTemperature());
client.println(" &deg;C</span></p>");
 
client.println("<p style=color:BLUE;font-size:160%>Pressure=<span class=\"sensor\">");
client.println(baro.getPressure());
client.println(" pa</span></td>"); 

client.println("<p style=color:BLACK;font-size:160%>Altitude=<span class=\"sensor\">");
client.println(baro.getAltitude());
client.println(" meters</span></td>");
 
client.println("</body></html>"); 
client.println();
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
