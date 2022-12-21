const int adcPin = 34; 
const int pwmPIN = 12;  

 int RCValue = 0;
 int pwm_val = 0;


 float Kp = 0;   // kp is the proportional term
 float Ki = 1.0; // ki is the integral term 
 float Kd = 1.0; // kd is the derivative term
 float sp = 2;     // sp is the setpoint 
 float y_1 = 0;    // y_1 is the prev value 
 float integral = 0;
 float derivative = 0;                                             
 float y = 0;
 int c = 0;
 float p = 0;
 float p_1 = 0;
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
   Ki = atof(strtok(NULL, ";"));
   Kd = atof(strtok(NULL, ";"));
   
    //  Serial.println("Kp");
   //   Serial.println(Kp);
   //   Serial.println("Ki");
   //   Serial.println(Ki);
  //    Serial.println("Kd");
  //    Serial.println(Kd);
  
} 
       
  p = (sp-y_1); // here (sp-y_1) is to finding the error; because {setpoint-prev value = error}, so p is the error.
  
  integral = integral +(sp-y_1)*dt;
 
  derivative = (p-p_1)/dt;
   //printf("Kp = %f, Ki = %f, Kd = %f\n",Kp,Ki,Kd);
  c = Kp*p +Ki*integral +Kd*derivative; 

 y_1 = analogRead(adcPin);
  y_1 = y_1*(3.3/4095.0);
  p_1 = p;
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
