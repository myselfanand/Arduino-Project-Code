#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include "Ubidots.h"

Adafruit_MPL3115A2 baro;

//WiFiClient client;
const char* UBIDOTS_TOKEN = "BBFF-bdoPea82SQ5UZVWOWsxe0yjp1QAyWQ"; 
const char* ssid     = "JCBRO"; // Your ssid
const char* password = "jcbro@321"; // Your Password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() {
  Serial.begin(115200);
  delay(100);
  if (!baro.begin()) {
  Serial.println("Could not find a valid MPL3115A2 sensor, check wiring!");
  while (1) {}
  }
ubidots.wifiConnect(ssid, password);
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi is connected");

 // use to set sea level pressure for current location
  // this is needed for accurate altitude measurement
  // STD SLP = 1013.26 hPa
 baro.setSeaPressure(1013.26);
}
void loop() { 
  float p = baro.getPressure();
  Serial.print("Pressure = ");
  Serial.print(p);
  Serial.println("pa");
  
  float a = baro.getAltitude();
  Serial.print("Altitude = ");
  Serial.print(a);
  Serial.println("meter");
  
  float temperature = baro.getTemperature();
  Serial.print("Temperature= ");
  Serial.print(temperature);
  Serial.println("°C");
  
  ubidots.add("Temperature", temperature);// Change for your variable name  
  ubidots.add("Pressure", p);
  ubidots.add("Altitude", a);
  
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id
  if (bufferSent) {
   Serial.println("Values sent by the device");
  }
  delay(3000);
}
