const int motorPin1  = 32;    // Pin 15 of L293D IC
const int motorPin2  = 33;    // Pin 10 of L293D IC                              
const int pwmPin = 12;       // Pin 1 of L293D IC
int speed = 0;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup()
{  
    pinMode(pwmPin, OUTPUT);   // where the motor is connected to
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    Serial.begin(115200);
    Serial.println("Enter values between 0 - 255");
    
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin, ledChannel);
}



void loop()
{
  
  if(Serial.available())         
    { 
      speed = Serial.parseInt();  //Receive Value from serial monitor
      Serial.println(speed);
      
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
     }

      if(speed > 255)
  {
    speed = 255;
  }
  else if(speed < 0)
  {
   speed = 0;
  }
  else
  {
   
  }
  ledcWrite(ledChannel,speed);
}
