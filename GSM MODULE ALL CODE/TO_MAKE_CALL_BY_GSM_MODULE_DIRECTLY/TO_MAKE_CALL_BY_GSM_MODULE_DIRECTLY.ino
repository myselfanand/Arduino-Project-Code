#include<SoftwareSerial.h>
SoftwareSerial gsm(2,3);

void setup()
{
  delay(10000);
  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("ATDxxxxxxxxxx;"); //replace x by your number
  delay(100);
  gsm.println("ATH");
}
void loop()
{
  
}
