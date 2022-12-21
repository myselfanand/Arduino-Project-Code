#include "WiFi.h"

const char* ssid = "JCBRO";
const char* password = "jcbro@321";

void setup() {

Serial.begin(115200);
Serial.print("Connecting to Wifi Network: ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Successfully connected to WiFi.");
}

void loop() {}
