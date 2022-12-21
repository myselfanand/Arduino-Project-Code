#include <HCSR04.h>
#include <WiFi.h>
#include<WebServer.h>
#include<DHT.h>


const char* ssid = "JCBRO";  
const char* password = "jcbro@321";
WebServer server(80);



//here is the code starting for dht sensor

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11

// DHT Sensor Pin Number //
uint8_t DHTPin = 19; 
DHT dht(DHTPin, DHTTYPE);  

float Temperature;
float Humidity;



//here is the code starting for ultrasonic sensor //
int trigPin=5;
int echoPin=18;

long duration;
int distance;

void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  delay(1000);




  //pin define here of dht sensor
  pinMode(DHTPin, INPUT);

  dht.begin();              

  
  Serial.println("Connecting to ");
  Serial.println(ssid);

 //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");


}

void loop(){

digitalWrite(trigPin, LOW);
delayMicroseconds(10);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

Serial.print("Distance: ");
Serial.println(distance );
delay (1000);

//here is the code for creating a web page //

server.handleClient();
}
void handle_OnConnect(){

  
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
 server.send(200, "text/html", SendHTML(distance,Temperature,Humidity));  
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
String SendHTML(float Distance,float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP32 ultrasonic and DHT Report</title>\n";


  ptr +="var x = setInterval(function(){loadData(\"data.txt\",updateData)}, 1000);\r\n";
  ptr += "function loadData(url, callback){\r\n";
  ptr +="var xhttp = new XMLHttpRequest();\r\n";
  ptr +="xhttp.onreadystatechange = function(){\r\n";
  ptr +="if(this.readyState == 4 && this.status == 200){\r\n";
  ptr += " callback.apply(xhttp);\r\n";

  
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";

 

  
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 ultrasonic and DHT Report</h1>\n";


  ptr +="<p>Distance: ";
  ptr +=(String)Distance;
  ptr +="cm</p>";


 ptr +="<p>Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";


 
   
 ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
  
