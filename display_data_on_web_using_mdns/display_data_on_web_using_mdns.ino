#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif


char webpage[] PROGMEM = R"=====(


<HTML>
  <HEAD>
      <TITLE>My first web page</TITLE>
  </HEAD>
<BODY Style=background-color:YELLOW; font-size:150%>
  <center>
      <h style=color:PURPLE;font-size:200%>Welcome to our Dynamic Web Page &#128515;</h>
 <center> <br>
<img src="image link paste here" alt="download" width="500" height="333;"> <br>
<h2 style=color:RED> Thank You so Much ! &#10084 </h2>
</BODY>
</HTML>

)=====";


#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{

  Serial.begin(9600);
  
  WiFi.softAP("techiesms", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 

  request->send_P(200, "text/html", webpage);
  });

   server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    
  request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
}
