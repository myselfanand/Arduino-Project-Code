const int adcPin = 34; 
const int pwmPIN = 12;  

 int RCValue = 0;
 int pwm_val = 0;


 float Kp = 0;
 float Ki = 1.0;
 int sp = 3;
 int y_1 = 0;
 int integral = 0;                                              
 int y = 0;
 int c = 0;
 int p;
 float dt=0.1;
 int i;
 String serialResponse;
 char temp[20];

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);

  
  pinMode(adcPin, INPUT);
   Serial.begin(115200);
   delay(1000);
}

  void loop()
{
   if ( Serial.available()) {
   serialResponse = Serial.readString();
   serialResponse.toCharArray(temp, serialResponse.length()); 
//   Serial.println(temp); 
   Kp = atof(strtok(temp, ";"));
   Ki = atof(strtok(temp, ";"));
//   Serial.println("Kp");
//   Serial.println(Kp);
//   Serial.println("Ki");
//   Serial.println(Ki);
}        
  p = (sp-y_1);
  
  integral = integral +(sp-y_1)*dt;
  
   
  c = Kp*p +Ki*integral; 

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
