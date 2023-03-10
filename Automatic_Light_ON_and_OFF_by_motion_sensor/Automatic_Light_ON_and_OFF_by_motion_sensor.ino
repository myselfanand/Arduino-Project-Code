int ledPin = 2;                // choose the pin for the LED
int ledPin1 = 33;   
int ledPin2 = 25;   
int ledPin3 = 26;   
int ledPin4 = 12;   

int inputPin = 14;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
   pinMode(ledPin1, OUTPUT);    
    pinMode(ledPin2, OUTPUT);    
     pinMode(ledPin3, OUTPUT);    
      pinMode(ledPin4, OUTPUT);    
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH)  // check if the input is HIGH
  {            
    digitalWrite(ledPin, HIGH);  // turn LED ON
     digitalWrite(ledPin1, HIGH);  
      digitalWrite(ledPin2, HIGH);  
       digitalWrite(ledPin3, HIGH);  
        digitalWrite(ledPin4, HIGH); 
  
    if (pirState == LOW) 
  {
      Serial.println("Motion detected!"); // print on output change
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
     digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, LOW);  
       digitalWrite(ledPin3, LOW);  
        digitalWrite(ledPin4, LOW); 
  
    if (pirState == HIGH)
  {
      Serial.println("Motion ended!");  // print on output change
      pirState = LOW;
    }
  }
}
