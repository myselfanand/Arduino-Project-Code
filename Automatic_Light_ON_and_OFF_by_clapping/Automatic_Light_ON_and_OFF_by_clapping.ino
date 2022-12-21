int soundSensor=33;
int LED =2;
int LED1 = 25;
int LED2 = 26;
int LED3 = 27;
int LED4 = 14;
int LED5 = 12;
boolean LEDStatus=false;

void setup() {
 Serial.begin(115200);
 pinMode(soundSensor,INPUT);
 pinMode(LED,OUTPUT);
 pinMode(LED1,OUTPUT);
 pinMode(LED2,OUTPUT);
 pinMode(LED3,OUTPUT);
 pinMode(LED4,OUTPUT);
 pinMode(LED5,OUTPUT);
 

}

void loop() {

  int SensorData=digitalRead(soundSensor); 
  if(SensorData==1){

    if(LEDStatus==false){
        LEDStatus=true;
        digitalWrite(LED,HIGH);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);
        digitalWrite(LED5,HIGH);
        Serial.println("Lights ON");
        delay(500);
    }
    else{
        LEDStatus=false;
        digitalWrite(LED,LOW);
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        Serial.println("Lights OFF");
        delay(500);
    }
  }
 } 
