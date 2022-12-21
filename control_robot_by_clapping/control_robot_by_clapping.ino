int sound = 14;
int st = 0;

#define motor1pin1 26
#define motor1pin2 27
#define motor2pin1 32
#define motor2pin2 33

int cont = 0;

void Forward()

{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
//  delay(1000);
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  motor3.run(RELEASE);
//  motor4.run(RELEASE);

}

void Backward()

{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
//  delay(1000);
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  motor3.run(RELEASE);
//  motor4.run(RELEASE);
}
void Left()

{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
//  delay(500);
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  motor3.run(RELEASE);
//  motor4.run(RELEASE);

}

void Right()

{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
//  delay(500);
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  motor3.run(RELEASE);
//  motor4.run(RELEASE);

}

void setup()

{
Serial.begin(115200);
//put your setup code here,to run once;
pinMode(motor1pin1, OUTPUT);
pinMode(motor1pin2, OUTPUT);
pinMode(motor2pin1, OUTPUT);
pinMode(motor2pin2, OUTPUT);
pinMode(sound, INPUT);

}

void loop()

{

//put your main code here,to run repeatedly;

  if (digitalRead(sound) == HIGH) {
    delay(10);
    if (cont == 0)
      st = millis();
    cont = cont + 1;
    while (digitalRead(sound) != LOW) {
      if (millis() - st > 2000) {
        Serial.print(cont);
        Serial.println(" aplausos");

        doOrders(cont);
        cont = 0;
      }
    }
  }
  if (millis() - st > 2000 && cont != 0) {
    Serial.print(cont);
    Serial.println(" aplausos");
    doOrders(cont);
    cont = 0;
  }
}
void doOrders(int apl) {
 if (cont==1)

{

Forward();
Serial.println("Move Forward");

}

else if (cont == 2)

{

Backward();
Serial.println("Move Backward");


}

else if (cont == 3)
{

Left();
Serial.println("Move Left");


}

else if (cont == 4)

{

Right();
Serial.println("Move Right");


}
}
