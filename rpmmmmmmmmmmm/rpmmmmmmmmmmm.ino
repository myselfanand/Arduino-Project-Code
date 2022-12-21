int dataIN = 14;               // IR sensor INPUT
int motorpin1 = 32;           // here we define the motor pin 
int motorpin2 = 33;          // here we define the motor pin 

int rpm; // RPM value
unsigned int currentTime;  // Current state of IR input scan
unsigned int endTime;
boolean currentState;
unsigned long td = 0;    // time duration


void setup()
{
  Serial.begin(115200);
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(dataIN,INPUT);       
}

void loop () {
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
  
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

 if (rpm > 550) 
 {
  rpm = 530; 
 }
 else if (rpm < 0) 
 {
  rpm = 0;
 }
 
  Serial.print("RPM:");
  Serial.println(rpm);
  delay(100);
}
