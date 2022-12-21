#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "JCBRO";  // Enter your SSID here
const char* password = "jcbro@321";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(9600);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_Root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body Style=background-color:YELLOW; font-size:150%>\
<h1style=color:PURPLE;font-size:200%>Welcome to our Dynamic Web Page &#128515;</h1>\
<img src="https://images.unsplash.com/photo-1466611653911-95081537e5b7?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxzZWFyY2h8MXx8ZW52aXJvbm1lbnR8ZW58MHx8MHx8&auto=format&fit=crop&w=800&q=60)"alt="download" width="500" height="333;">\
</body>\
</html>";

// Handle root url (/)
void handle_Root() {
  server.send(200, "text/html", HTML);
}
