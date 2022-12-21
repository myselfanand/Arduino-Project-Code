#include "WiFi.h"
#include "DHT.h"
#include "AWS_IOT.h"

#define DHT_PIN 4 // pin connected to data pin of DHT11
#define DHT_TYPE DHT11  // Type of the DHT Sensor, DHT11/DHT22

#define WIFI_SSID "JCBRO" // SSID of your WIFI
#define WIFI_PASSWD "jcbro@321" //your wifi password

#define CLIENT_ID "temp_esp32"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/temp_esp32/shadow" //topic for the MQTT data
#define AWS_HOST "a3aca60dtp1m7y-ats.iot.ap-south-1.amazonaws.com" // your host for uploading data to AWS,

DHT dht(DHT_PIN, DHT_TYPE);
AWS_IOT aws;
void setup(){
  Serial.begin(115200);
  Serial.print("\nInitializing thing temp_esp32 \n");
  Serial.print("\n  Initializing WIFI: Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  Serial.print("  ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n  Connected.\n  Done");
  Serial.print("\n  Initializing DHT11...");
  dht.begin();
  Serial.println("  Done.");
  Serial.println("\n  Initializing connetction to AWS....");
  if(aws.connect(AWS_HOST, CLIENT_ID) == 0){ // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
}
void loop(){
  // read temperature and humidity
  float temp = dht.readTemperature(); // return temperature in °C
  float humidity = dht.readHumidity();// return humidity in %
  // check whether reading was successful or not
  if(temp == NAN || humidity == NAN){ // NAN means no available data
    Serial.println("Reading failed.");
  }
  else{
    //create string payload for publishing
    String temp_esp32 = "Temperature: ";
    temp_esp32 += String(temp);
    temp_esp32 += "°C Humidity: ";
    temp_esp32 += String(humidity);
    temp_esp32 += " %";
   
    char payload[40];
    temp_humidity.toCharArray(payload, 40);
    Serial.println("Publishing:- ");
    Serial.println(payload);
     if(aws.publish(MQTT_TOPIC, payload) == 0){// publishes payload and returns 0 upon success
      Serial.println("Success\n");
    }
    else{
      Serial.println("Failed!\n");
    }
  }
  delay(1000);
}
