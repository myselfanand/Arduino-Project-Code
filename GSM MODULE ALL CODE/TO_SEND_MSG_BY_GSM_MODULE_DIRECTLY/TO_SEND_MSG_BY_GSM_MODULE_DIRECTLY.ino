#include<SoftwareSerial.h>
SoftwareSerial gsm(25,26);

void setup()
{
  delay(10000);
  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); //replace x by your number
  delay(1000);
  gsm.println("hello I AM ANAND");
  delay(100);
  gsm.println((char)26);
  delay(1000);
}
void loop()
{
  
}
