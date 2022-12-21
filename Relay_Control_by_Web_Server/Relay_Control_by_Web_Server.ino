#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "JCBRO"; // Input your wifi network name
const char* password = "jcbro@321"; // Input your wifi password

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String relay1State = "off";
String relay2State = "off";
String relay3State = "off";
String relay4State = "off";

// Assign output variables to GPIO pins
const int relay1 = 13; // GPIO5 D1
const int relay2 = 14; // GPIO4 D2
const int relay3 = 18; // GPIO0 D3
const int relay4 = 19; // GPIO2 D4


void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  // Set outputs to HIGH. relay active LOW
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == 'n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            
            // turns the GPIOs on and off
            if (header.indexOf("GET /13/on") >= 0)
            {
              Serial.println("GPIO 13 on");
              relay1State = "on";
              digitalWrite(relay1, LOW);
            }
            else if (header.indexOf("GET /13/off") >= 0)
            {
              Serial.println("GPIO 13 off");
              relay1State = "off";
              digitalWrite(relay1, HIGH);
            }
            else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              relay2State = "on";
              digitalWrite(relay2, LOW);
            }
            else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              relay2State = "off";
              digitalWrite(relay2, HIGH);
            }
            else if (header.indexOf("GET /0/on") >= 0)
            {
              Serial.println("GPIO 0 on");
              relay3State = "on";
              digitalWrite(relay3, LOW);
            }
            else if (header.indexOf("GET /0/off") >= 0)
            {
              Serial.println("GPIO 0 off");
              relay3State = "off";
              digitalWrite(relay3, HIGH);
            }
            else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              relay4State = "on";
              digitalWrite(relay4, LOW);
            }
            else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              relay4State = "off";
              digitalWrite(relay4, HIGH);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
            //client.println("<link rel="icon" href="data:,">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html, body { font-family: Helvetica; display: block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #209e48; border: none; color: white; padding: 12px 24px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #c20a0a;}");
            client.println(".textbox {width: 80px; border: 1px solid #333; padding: 16px 20px 0px 24px; background-image: linear-gradient(180deg, #fff, #ddd 40%, #ccc);}");
            client.println(".mytext {font-size: 16px; font-weight:bold; font-family:Arial ; text-align: justify;}");
            client.println("#container {width: 100%; height: 100%; margin-left: 5px; margin-top: 20px; padding: 10px; display: -webkit-flex; -webkit-justify-content: center; display: flex; justify-content: center;} ");
            client.println("</style></head>");
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server Relay Control</h1>");
            // Display current state, and ON/OFF buttons for GPIO 5
            client.println("<div id=\"container\">");
            client.println("<p><div class=\"textbox mytext\">RELAY 1 </div> ");
            // If the relay1State is off, it displays the ON button
            if (relay1State == "off") {
              client.println("<a href=\"/5/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<a href=\"/5/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            client.println("</div>");
            // Display current state, and ON/OFF buttons for GPIO 4
            client.println("<div id=\"container\">");
            client.println("<p><div class=\"textbox mytext\">RELAY 2 </div> ");
            // If the relay2State is off, it displays the ON button
            if (relay2State == "off") {
              client.println("<a href=\"/4/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<a href=\"/4/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            client.println("</div>");
            // Display current state, and ON/OFF buttons for GPIO 0
            client.println("<div id=\"container\">");
            client.println("<p><div class=\"textbox mytext\">RELAY 3 </div>");
            // If the relay1State is off, it displays the ON button
            if (relay3State == "off") {
              client.println("<a href=\"/0/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<a href=\"/0/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            client.println("</div>");
            // Display current state, and ON/OFF buttons for GPIO 2
            client.println("<div id=\"container\">");
            client.println("<p><div class=\"textbox mytext\">RELAY 4 </div>");
            // If the relay2State is off, it displays the ON button
            if (relay4State == "off") {
              client.println("<a href=\"/2/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<a href=\"/2/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            client.println("</div>");
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != 'r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
