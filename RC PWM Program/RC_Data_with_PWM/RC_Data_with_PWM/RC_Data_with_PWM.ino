// the number of the LED pin
const int adcPin = 34;  // 16 corresponds to GPIO16
const int pwmPIN = 12;  // 16 corresponds to GPIO16


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 int RCValue =0;
void setup(){
  
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq,resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPIN, ledChannel);

  ledcWrite(ledChannel, 128); 
  
  pinMode(adcPin, INPUT);
   Serial.begin(115200);
   delay(1000);
}
 
void loop(){
  
  
  // read the input on analog pin 34:
  RCValue = analogRead(adcPin);
  //  Serial.print("RCValue:");
  Serial.println(RCValue);
  delay(100);
}
