int dataIN = 14;               // IR sensor INPUT
int motorpin1 = 32;           // here we define the motor pin 
int motorpin2 = 33;          // here we define the motor pin 

boolean currentState;
int rpm; // RPM value
unsigned int currentTime;     // Current state of IR input scan
unsigned int endTime;
unsigned long td = 0;


 const int pwmPIN = 12;  
 const int pwm_val = 0;

 float Kp = 100;     // kp is the proportional term
 float Ki = 0;      // ki is the integral term 
 float Kd = 0;     // kd is the derivative term
 
 float sp = 350;   // sp is the setpoint 
 float integral = 0;
 float derivative = 0;
 
 float c = 0; // output
 float p = 0;  // error
 float p_1 = 0;  // prev error 
 float dt=0.01;  //  loop time duration
 String serialResponse;
 char temp[20];

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

 
void setup()
{
  Serial.begin(115200);
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(dataIN,INPUT);  

       digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  
   // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);

  ledcWrite(ledChannel, 100);
  
}
 void RPM()
{
  
  while (!digitalRead(dataIN))
  {
    
  }
  currentTime = micros();
  currentState = 1;
  
  while (currentState == digitalRead(dataIN))
  {
    
  }
  currentState = 0;
  while (!digitalRead(dataIN)) 
  {
   
  }
  endTime = micros();
  

  td = endTime-currentTime; // time distance
  
  rpm = (60000000/td);
  
   if (rpm > 530) 
   {
    rpm = 530;
   }
   else if (rpm < 0)
   {
    rpm = 0;
   }
   
}
  void loop() {
    
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  
   if ( Serial.available()) {
   serialResponse = Serial.readString();
   serialResponse.toCharArray(temp, serialResponse.length()); 

   Kp = atof(strtok(temp, ";"));
   Ki = atof(strtok(NULL, ";"));
   Kd = atof(strtok(NULL, ";"));
} 
   RPM();
   p = (sp-rpm); // here (sp-rpm) is to finding the error; because {setpoint-prev value = error}, so p is the error.  
   integral = (integral + p)*dt;
   derivative = (p-p_1)/dt;
   p_1 = p;
   
//   printf("Kp = %f, Ki = %f, Kd = %f\n",Kp,Ki,Kd);
 
  c = Kp*p +Ki*integral +Kd*derivative; 
    
  if(c > 255)
  {
    c = 255;
  }
  else if(c < 80)
  {
    c = 80;
  }
  else
  {
   
  }
  ledcWrite(ledChannel, c); 
  Serial.println(rpm);
  delay(10);
}
