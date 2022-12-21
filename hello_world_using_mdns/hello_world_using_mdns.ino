#include<ESPmDNS.h>
#include<WiFi.h>
#include<ESPAsyncWebServer.h>
  
const char* ssid = "JCBRO";
const char* password =  "jcbro@321";
  
AsyncWebServer server(80);
  
void setup(){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }  
  Serial.println(WiFi.localIP());
  
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "hello guys");
  });
  
  server.begin();
}
  
void loop(){}
