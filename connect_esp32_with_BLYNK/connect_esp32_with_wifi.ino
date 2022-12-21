#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
int pin = 2;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "SqdQu9a2GJDG4ehcvQgWXawOczHc_EoU";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "realme 3 Pro";
char pass[] = "1967bcea48bakg";

void setup() {  
  pinMode(pin, OUTPUT); 
  pinMode(pin, HIGH);
  Serial.begin(9600);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin("SqdQu9a2GJDG4ehcvQgWXawOczHc_EoU",ssid,pass);
}
void loop(){
    Blynk.run();
}
