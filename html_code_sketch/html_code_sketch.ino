
#include <WiFi.h>
#include <WebServer.h>

//SSID and Password of your WiFi router
const char* ssid = "JCBRO";
const char* password = "jcbro@321";

WebServer server(80); //Server on port 80


void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <TITLE>My first web page</TITLE>
  </HEAD>
<BODY>
  <CENTER>
      <B>Hello World.... </B>
  </CENTER> 
</BODY>
</HTML>
)=====";

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void loop(void){
  server.handleClient();          //Handle client requests
}
