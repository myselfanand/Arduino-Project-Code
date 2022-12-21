
int motor1Pin1= 25;
int motor1Pin2= 26;

int motor2Pin1= 18;
int motor2Pin2= 19;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(motor1Pin1,OUTPUT);
pinMode(motor1Pin2,OUTPUT);

pinMode(motor2Pin1,OUTPUT);
pinMode(motor2Pin2,OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("MOVING FORWARD");
digitalWrite(motor1Pin1,HIGH);
digitalWrite(motor1Pin2,LOW);

digitalWrite(motor2Pin1,HIGH);
digitalWrite(motor2Pin2,LOW);
delay(5000);

Serial.println("MOVING BACKWARD");
digitalWrite(motor1Pin1,LOW);
digitalWrite(motor1Pin2,HIGH);

digitalWrite(motor2Pin1,LOW);
digitalWrite(motor2Pin2,HIGH);
delay(2000);

}
