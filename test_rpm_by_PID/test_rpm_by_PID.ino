int motorpin1 = 32; // define the motor pin 
int motorpin2 = 33; //define the motor pin 
int pwm_val = 0;
const int pwmPIN = 26; // enablePin of the motor 

const int IR_pin = 14; // IR SENSOR Pin
unsigned long prevmicros; // To store time
unsigned long duration; // To store time difference
unsigned long Serialrefresh; // To store time for lcd to refresh

int rpm; // RPM value
int currentstate; // Current state of IR input scan
int prevstate; // State of IR sensor in previous scan

 float Kp = 0;   // kp is the proportional term
 float Ki = 1.0; // ki is the integral term 
 float Kd = 1.0; // kd is the derivative term
 float sp = 350; // sp is the setpoint 
 float p = 0;    // p is to cal error
 float integral = 0; 
 float derivative = 0;
 float dt = 0.2;   // time of loop
 String serialResponse;  // here we are storing string data which recieve from serial monitor
 char temp[20];   // store max 20char
 float p_1 = 0;   // this is the prev error
 float op = 0;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);
 
  pinMode(IR_pin , INPUT);
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  prevmicros = 0;
  prevstate = 0;  
  Serial.begin(115200);
   delay(500);
}

void loop()
{
   if ( Serial.available()) {
   serialResponse = Serial.readString();
   serialResponse.toCharArray(temp, serialResponse.length()); 

   Kp = atof(strtok(temp, ";"));
   Ki = atof(strtok(NULL, ";"));
   Kd = atof(strtok(NULL, ";"));   
}
   cal_rpmFun();
   prevstate = rpm;       
   p = (sp-prevstate); // here we find error & p is the error; because {setpoint-prevalue = error}.

   p_1 = p;
   
  integral = integral +p*dt;  // here integral = integral+error*dt
 
  derivative = (p-p_1)/dt;     // here derivative = error-preverror/dt
  
  op= Kp*p +Ki*integral +Kd*derivative;  // here we calculate the pid        
  
  if( op > 255)
  {
    op= 255;
  }
  else if(op < 0)
  {
    op = 0;
  }
  else
  {
    
  }
  ledcWrite(ledChannel, op);
  Serial.println(rpm);
  delay(100);
  }

  void cal_rpmFun () {
    
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  
  currentstate = digitalRead(IR_pin); // Read IR sensor state
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from HIGH to LOW
       {
         duration = ( micros() - prevmicros ); // Time difference between revolution in microsecond
         rpm = (30000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         prevmicros = micros(); // store time for next revolution calculation
       }
   }
     
  prevstate = currentstate; // store this scan (prev scan) data for next scan
   
  if( ( millis()-Serialrefresh ) >= 100 )
    {    
//      Serial.print("RPM :");
//      Serial.println(rpm);  // here we are printing rpm val on serial monitor
      delay(100);
    }
}
