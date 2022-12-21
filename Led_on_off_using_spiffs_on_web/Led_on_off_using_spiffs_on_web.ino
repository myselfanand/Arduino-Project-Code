// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "Enter_Your_WiFi_Name"; //Replace with your own SSID
const char* password = "Enter_Your_WiFi_Password"; //Replace with your own password

const int ledPin = 2;
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "GPIO_STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}

<!DOCTYPE html>
<html>
<head>
  <title>ESP32 WEB SERVER</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body style=background-color:RED align=center>
  <h2 style=background-color:white;font-size:300%>ESP32 WEB SERVER</h2>
  <div class="content">
    <div class="card-grid">
      <div class="card">
        <p style=color:yellow;font-size:200%>GPIO state: <strong>GPIO_STATE</strong></p>
        <p>
          <a href="/led2on"><button style=font-size:150%; class="button">ON</button></a>
          <a href="/led2off"><button style=font-size:150%; class="button button2">OFF</button></a>
        </p>
      </div>
    </div>
  </div>
</body>

</html>
 
void loop(){
  
}
