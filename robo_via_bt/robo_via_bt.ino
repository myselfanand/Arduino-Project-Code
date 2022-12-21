
#include<BluetoothSerial.h>

String readrobo;
int k=0;
void setup() {
Serial.begin(9600);
pinMode(25,OUTPUT);
pinMode(26,OUTPUT);
pinMode(32,OUTPUT);
pinMode(33,OUTPUT);
}
 
void loop() {
while (Serial.available())
{
delay(1000);
char c = Serial.read();
readrobo += c;
}
 
if(readrobo.length() > 0)
{
Serial.println(readrobo);
 
if(readrobo == "forward")
{
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);
k=1;
}
 
if(readrobo == "backward")
{
digitalWrite(25, LOW);
digitalWrite(26, HIGH);
digitalWrite(32, LOW);
digitalWrite(33, HIGH);
k=2;
}
 
if(readrobo == "right")
{
if (k==2)
{
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
delay(1000);
digitalWrite(25, LOW);
digitalWrite(26, HIGH);
digitalWrite(32, LOW);
digitalWrite(33, HIGH);
}
else
{
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
delay(1000);
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);
}
}
 
if(readrobo == "left")
{
if (k==2)
{
digitalWrite(25, LOW);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);
delay(1000);
digitalWrite(25, LOW);
digitalWrite(26, HIGH);
digitalWrite(32, LOW);
digitalWrite(33, HIGH);
}
else
{
digitalWrite(25, LOW);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);
delay(1000);
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);
}
}
 
if(readrobo == "stop")
{
digitalWrite(25, LOW);
digitalWrite(26, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);
}
}
readrobo="";
}

 
