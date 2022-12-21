//Receiver code 
//all the best

#include<SoftwareSerial.h>
SoftwareSerial MyBlue(18,19);
char x_axis=0,y_axis=0;

void setup() {
pinMode(25, OUTPUT);
pinMode(26, OUTPUT);
pinMode(32, OUTPUT);
pinMode(33, OUTPUT);

Serial.begin(115200);
MyBlue.begin(38400);
}

void loop() {
if(MyBlue.available()>0)
{
x_axis= MyBlue.read();
Serial.println(x_axis);
if(x_axis=='F')

{
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);

}

else if(x_axis=='B')

{
digitalWrite(25, LOW);
digitalWrite(26, HIGH);
digitalWrite(32, LOW);
digitalWrite(33, HIGH);

}

else if(x_axis=='R')

{
digitalWrite(25, LOW);
digitalWrite(26, HIGH);
digitalWrite(32, HIGH);
digitalWrite(33, LOW);

}
else if(x_axis=='L')

{
digitalWrite(25, HIGH);
digitalWrite(26, LOW);
digitalWrite(32, LOW);
digitalWrite(33, HIGH);

}

else if(x_axis=='S')

{
digitalWrite(25, LOW);
digitalWrite(26, LOW);
digitalWrite(32, LOW);
digitalWrite(33, LOW);

}
//else
//
//{
//digitalWrite(25, LOW);
//digitalWrite(26, LOW);
//digitalWrite(32, LOW);
//digitalWrite(33, LOW);
//}

   }
}
