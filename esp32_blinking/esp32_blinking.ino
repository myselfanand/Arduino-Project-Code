int ledPin = 2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (ledPin,OUTPUT);}
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(ledPin, HIGH);
delay(1000);
digitalWrite(ledPin,LOW);
delay(1000);
if(ledPin, HIGH);
Serial.println("on");
delay(1000);
if(ledPin,LOW);
Serial.println("off");
delay(1000);
}
