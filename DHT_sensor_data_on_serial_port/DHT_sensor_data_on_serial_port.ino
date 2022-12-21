#include "DHT.h"

#define DHTPIN 14

DHT dht(DHTPIN, DHT11);

void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temperature :");
  Serial.print(temp);
  Serial.println("°C");

  Serial.print("Humidity :");
  Serial.println(humi);
  delay(1000);
}
