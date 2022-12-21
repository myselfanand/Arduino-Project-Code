#include <Adafruit_MPL3115A2.h>
#include <WiFi.h> 
#include <Wire.h>

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
Serial.println(" *C");

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
String request = client.readStringUntil('\r'); 
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("</style></head><body><h1>ESP32 Web Server BMP180</h1>");
client.println("<h2>BMP180 Barometic sensor</h2>");
client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
client.println("<tr><td>Temp. Celsius</td><td><span class=\"sensor\">");
client.println(baro.getTemperature());
client.println(" *C</span></td></tr>"); 
client.println("<tr><td>Pressure</td><td><span class=\"sensor\">");
client.println(baro.getPressure());
client.println(" pa</span></td></tr>"); 
client.println("<tr><td>Altitude</td><td><span class=\"sensor\">");
client.println(baro.getAltitude());
client.println(" meters</span></td></tr>"); 
client.println("</body></html>"); 
client.println();
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
