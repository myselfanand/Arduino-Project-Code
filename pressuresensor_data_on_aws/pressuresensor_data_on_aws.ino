#include "WiFi.h"
#include "Adafruit_MPL3115A2.h"
#include "AWS_IOT.h"

#define WIFI_SSID "JCBRO" // SSID of your WIFI
#define WIFI_PASSWD "jcbro@321" //your wifi password

#define CLIENT_ID "temp_esp32db"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/temp_esp32/shadow" //topic for the MQTT data
#define AWS_HOST "a3aca60dtp1m7y-ats.iot.ap-south-1.amazonaws.com" // your host for uploading data to AWS,

Adafruit_MPL3115A2 baro;
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
  Serial.print("\n  Initializing MPL3115A2...");
  baro.begin();
  Serial.println("  Done.");
  Serial.println("\n  Initializing connetction to AWS....");
  if(aws.connect(AWS_HOST, CLIENT_ID) == 0){ // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
   baro.setSeaPressure(1013.26);
}
void loop(){
  // read temperature and humidity
  
  float pressure = baro.getPressure();// return humidity in %
  float altitude = baro.getAltitude();//
  float temperature = baro.getTemperature();
  
  // check whether reading was successful or not
  if(pressure == NAN || altitude == NAN) { // NAN means no available data
    Serial.println("Reading failed.");
  }
  else{
    //create string payload for publishing
   
    String pressure_sensor = "Pressure:";
    pressure_sensor += String(pressure);
    pressure_sensor += "pa Altitude:";
    pressure_sensor += String(altitude);
    pressure_sensor += "meter Temperature:";
    pressure_sensor += String(temperature);
    pressure_sensor += "°C";
    
   
    char payload[100];
    pressure_sensor.toCharArray(payload, 100);
    Serial.println("Publishing:- ");
    Serial.println(payload);
     if(aws.publish(CLIENT_ID, payload) == 0){// publishes payload and returns 0 upon success
      Serial.println("Success\n");
    }
    else{
      Serial.println("Failed!\n");
    }
  }
  delay(1000);
}
