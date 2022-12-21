#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "JCBRO"; // Input your wifi network name
const char* password = "jcbro@321"; // Input your wifi password

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;



// Assign output variables to GPIO pins
const int relay1 = 13; // GPIO5 D1

void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  pinMode(relay1, OUTPUT);
 // Set outputs to HIGH. relay active LOW
 digitalWrite(relay1, HIGH);
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
            if (header.indexOf("GET /relayoff") >= 0)
            {
              Serial.println("GPIO 13 off");
            
              digitalWrite(relay1, HIGH);
            }
            else if (header.indexOf("GET /relayon") >= 0)
            {
              Serial.println("GPIO 13 on");
             
              digitalWrite(relay1, LOW);
            }
             
          client.print("<HTML><title>ESP32</title>");
          client.print("<body style=background-color:GREENYELLOW; ALIGN=CENTER ><h1 style=color:RED;font-size:500%;>ESP32 Relay Control</h1>");
          client.print("<h2 style=color:PURPLE;font-size:300%> Relay Control From Here &#128071;  </h2>");
          client.print("<a  href=\"/relayoff\"><button style =background-color:RED;color:WHITE;font-size:150% > SWITCHED OFF &#128161</button></a>");
          client.print("<a  href=\"/relayon\"\"><button  style =background-color:GREEN;color:WHITE;font-size:150% >SWITCHED ON &#128161</button></a>");
          client.print("</body></HTML>");
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
