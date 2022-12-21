#include <HCSR04.h>
#include <WiFi.h>
#include<WebServer.h>
#include<Ultrasonic.h>

const char* ssid = "JCBRO";  
const char* password = "jcbro@321";
WebServer server(80);




//here is the code starting for ultrasonic sensor //
int trigPin=5;
int echoPin=18;

long duration;
int distance;


String page = "";
String text = "";
double data;


void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  delay(1000);


  
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
server.on("/data.txt", []() {
    text = (String)data;
    server.send(200, "text/html", text);
  });
  server.on("/", []() {
    page = "<h1>ultrasonic sensor><h1>ultrasonic:</h1> <h1 id=\"data\">""</h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
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
    page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
digitalWrite(trigPin, LOW);
delayMicroseconds(10);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

 duration = pulseIn(echoPin, HIGH);
 distance = duration*0.034/2;
 data = distance;

Serial.println(distance);
delay (1000);

  server.handleClient();
}
