#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(18,19);//arduino rx,tx
#include <WiFi.h>
const char* ssid     = "JCBRO";
const char* password = "jcbro@321";
WiFiServer server(80);
String page;
void setup()
{
    Serial.begin(9600);
ss.begin(9600);
    Serial.print("Connecting to ");
    Serial.println(ssid);

WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");    // this is the address to use for viewing the map
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop(){
  smartdelay(1000);
 WiFiClient client = server.available();    // listen for incoming clients
    float flat, flon;
 
   gps.f_get_position(&flat, &flon);
  
  if (client) {                             
    Serial.println("new client");          
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            
      if (client.available()) {             // if there's client data
        char c = client.read();          // read a byte
          if (c == '\n') {                      // check for newline character,
          if (currentLine.length() == 0) {  // if line is blank it means its the end of the client HTTP request
      
page="<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta http-equiv='X-UA-Compatible' content='ie=edge'><title>Google Map On WEB SERVER</title><style>#map{height:400px;width:100%;}</style></head> <body><h1>Google Map on WEB SERVER</h1><div id='map'></div><script>function initMap(){var options = {zoom:8,center:{lat:";
    page+=flat;
    page+=",lng:";
    page+=flon;
    page+="}};var map = new google.maps.Map(document.getElementById('map'), options);google.maps.event.addListener(map, 'click', function(event){addMarker({coords:event.latLng});});var markers = [{coords:{lat:";
page+=flat;
page+=",lng:";
page+=flon;
page+="}}];for(var i = 0;i < markers.length;i++){addMarker(markers[i]);}function addMarker(props){var marker = new google.maps.Marker({position:props.coords,map:map,});if(props.iconImage){marker.setIcon(props.iconImage);}if(props.content){var infoWindow = new google.maps.InfoWindow({content:props.content});marker.addListener('click', function(){infoWindow.open(map, marker);});}}}</script><script async defer src='https://maps.googleapis.com/maps/api/js?key=AIzaSyBX9stiiXvkyMgjXB3pNrJTYBwA4b6v2Jc&callback=initMap'></script></body></html>";
 
 
 client.print(page);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {   currentLine = ""; }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
         // here you can check for any keypresses if your web server page has any
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    }
}
static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
