#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

const char* ssid = "JCBRO"; //Enter Wi-Fi SSID
const char* password =  "jcbro@321"; //Enter Wi-Fi Password

WebServer server(80);


String page = "";
String text = "";
float temp;
float humi;
 

#define DHT11PIN 4

DHT dht(DHT11PIN, DHT11);



void setup()
{
  Serial.begin(9600);
  delay(1000);
/* Start the DHT11 Sensor */
  dht.begin();

  
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/temp.txt", []() {
    text = (int)temp;
    server.send(200, "text/html", text);
  }); 
  server.on("/humi.txt", []() {
    text = (int)humi;
    server.send(200, "text/html", text);
  }); 
  server.on("/", []() { 

    page = "<h1>DHT SENSOR WHEATHER REPORT</h1>\r\n";
    page += "<h1>Temperature: <span id=\"temp\"></span>&deg;C</h1>\r\n";
    page += "<h2>HUMIDITY:    <span id=\"humi\"></span>%</h2>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"temp.txt\",updateData)}, 1000);\r\n";
    page += "var y = setInterval(function() {loadData(\"humi.txt\",updateData1)}, 1000);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += " document.getElementById(\"temp\").innerHTML = this.responseText;\r\n";
    page += "";
    page += "}\r\n";
    page += "function updateData1(){\r\n";
    page += "";
    page += " document.getElementById(\"humi\").innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}



void loop()
{
  temp = dht.readTemperature();
  humi = dht.readHumidity();
  


  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);
   server.handleClient();

}
