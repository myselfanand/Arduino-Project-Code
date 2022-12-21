const int trigPin = 34;
const int echoPin = 35;

int ledA=25;
int ledB=26;
int ledC=27;
int ledD=14;

int a=24;
int b=26;
int c=28;
int d=32;

//int max_distance = 200;

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
pinMode (ledA,OUTPUT);
pinMode (ledB,OUTPUT);
pinMode (ledC,OUTPUT);
pinMode (ledD,OUTPUT);

digitalWrite(ledA, LOW);
digitalWrite(ledB, LOW);
digitalWrite(ledC, LOW);
digitalWrite(ledD, LOW);
}


void loop() {
// put your main code here, to run repeatedly:
long duration, inches, cm;
pinMode(trigPin,OUTPUT);

digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);

digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);

duration = pulseIn(echoPin, HIGH);
//cm = ( duration / 29 ) / 2;
//inches = cm * 0.393701;
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

Serial.print(inches); 
Serial.print(" in"); 
Serial.print(cm); 
Serial.print(" cm"); 
Serial.println(); 
delay(100);

if (inches<=a) {digitalWrite (ledA,HIGH);digitalWrite (ledB,HIGH); digitalWrite (ledC,HIGH); digitalWrite (ledD,HIGH); }
else if (inches<=b){digitalWrite (ledA,LOW);digitalWrite (ledB,HIGH); digitalWrite (ledC,HIGH); digitalWrite (ledD,HIGH); }
else if (inches<=c){digitalWrite (ledA,LOW);digitalWrite (ledB,LOW); digitalWrite (ledC,HIGH); digitalWrite (ledD,HIGH);}
else if (inches<=d){digitalWrite (ledA,LOW);digitalWrite (ledB,LOW); digitalWrite (ledC,LOW); digitalWrite (ledD,HIGH); }
else {digitalWrite (ledA,LOW);digitalWrite (ledB,LOW); digitalWrite (ledC,LOW); digitalWrite (ledD,LOW); }
}

long microsecondsToInches(long microseconds) {
return (microseconds / 74) / 2;
}
long microsecondsToCentimeters(long microseconds) {
return (microseconds / 29) / 2;
}
