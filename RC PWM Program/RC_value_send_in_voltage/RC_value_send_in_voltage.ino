int RCValue = 0;                   // Variable to store the desired value
int adcPin = 34;           
int pwmPIN = 12;                          // PWM output pin


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
float pwm_val = 0.0;
int pwmi_val = 0;

float voltage;

void setup() {                // This executes once
  
  pinMode(adcPin, INPUT);
  Serial.begin(115200);             // Initialize serial port
  
  
    // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);
   
}

void loop() {                 // This loops continuously
  if(Serial.available()>0){         // Check if there's data
   pwm_val = Serial.parseFloat();           // Read said data into the variable ""
   //Serial.println(pwm_val);
   pwmi_val = (int)pwm_val*255/3.3;
   //Serial.println(pwmi_val);
   ledcWrite(ledChannel, pwmi_val); 
  }

 RCValue = analogRead(adcPin);
 // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 5V):
  voltage = RCValue*(3.3/4095.0);
   Serial.println(voltage);
   delay(50);      
  
}
