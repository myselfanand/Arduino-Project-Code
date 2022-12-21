
const int adcPin = 34; 
const int pwmPIN = 12;  

 int RCValue = 0;
 int pwm_val = 0;
      
 float y_1 = 0;
 int y = 0;
 int sp = 3;
 int c = 0;
 float Kd = 1.0;
 float dt= 0.1;
 int derivative = 0;
 int p = 0;
 


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){
  
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);

  
  pinMode(adcPin, INPUT);
   Serial.begin(115200);
   delay(1000);
}
 
void loop(){
  
  if(Serial.available()>0){         // Check if there's any data from serial port ;
   Kd = Serial.parseFloat();       //  Read said data into the variable ""
  }

  p = (sp-y_1);              // p is the error because (setpoint-prev value = error);
  derivative = (p-y_1)/dt;  // this is the formula to finding value of derivative {(derivative = error-prev value)/dt}
  c= Kd*derivative;
  
  y_1 = analogRead(adcPin);
  y_1 = y_1*(3.3/4095.0);
  if(c > 255)
  {
    c = 255;
  }
  else if(c < 0)
  {
    c = 0;
  }
  else
  {
    
  }
  ledcWrite(ledChannel, c); // write vtg
  Serial.println(y_1);
  delay(100);
}
