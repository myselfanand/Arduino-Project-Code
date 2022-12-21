int RCValue = 0;                   // Variable to store the desired value
int adcPin = 34;           
int pwmPIN = 12;                          // PWM output pin


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int pwm_val = 0;
void setup() {                // This executes once
  
  pinMode(adcPin, INPUT);
  Serial.begin(115200);             // Initialize serial port
  Serial.println("Enter values between 0 - 255");
  
    // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);
    
  
}

void loop() {                 // This loops continuously
  if(Serial.available()>0){         // Check if there's data
   pwm_val = Serial.parseInt();           // Read said data into the variable ""
   ledcWrite(ledChannel, pwm_val); 
  }

 RCValue = analogRead(adcPin);
//   Serial.print("RCValue");
   Serial.println(RCValue);
   delay(100);      
  
}
