#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue = 0;  // value from the analog pin

void setup() {
  Serial.begin(115200);
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() 
{
//  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
//  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)


  if(Serial.available())         
   { 
  potValue = Serial.parseInt();  //Receive Value from serial monitor
  Serial.println( potValue); 
   }   
  ESC.write(potValue);    // Send the signal to the ESC
  delay(2000);
  
//  Serial.println(potValue);
//  potValue += 2;
  
  if(potValue > 20)
  {
    potValue = 20;
  }
  
    else if (potValue < 0)
    {
    potValue = 0;
    }

    else
   {
   }
 
}
