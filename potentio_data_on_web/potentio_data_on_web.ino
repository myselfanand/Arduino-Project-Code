#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "JCBRO"; //Enter Wi-Fi SSID
const char* password =  "jcbro@321"; //Enter Wi-Fi Password

WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
String text = "";
double data;

int potPin = 34;
int potValue =0;

float voltage;

void setup(void) {
  pinMode(potPin, INPUT);
  Serial.begin(9600);
   delay(1000);
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
  server.on("/data.txt", []() {
    text = (String)data;
    server.send(200, "text/html", text);
  });
  server.on("/", []() {
    page = "<h1>Potentiometer Data</h1><h1>Potentio value in volt:</h1> <h1 id=\"data\">""</h1>\r\n";
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
  // read the input on analog pin 34:
  potValue = analogRead(potPin);
   // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 5V):
  voltage = potValue*(5.0/4095.0);
  data= voltage;
  Serial.print("voltage :");
  Serial.println(voltage);
  
  delay(1000);
  server.handleClient();
}
