int sound = 33;  // mic pin no.
int st = 0;

#define led1 25   // here we define our led pin no
#define led2 26
#define led3 27
#define led4 14
//#define led5 27

int cont = 0;   

void One_LED()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
//  digitalWrite(led5, LOW);  
}

void Two_LED()

{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH); 
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
//  digitalWrite(led5, LOW);  
}

void Three_LED()

{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
//  digitalWrite(led5, LOW);  

}

void Four_LED()

{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
//  digitalWrite(led5, LOW);  
}

//void FIVE_LED()
//
//{
//  digitalWrite(led1, HIGH);
//  digitalWrite(led2, HIGH);
//  digitalWrite(led3, HIGH);
//  digitalWrite(led4, HIGH);
//  digitalWrite(led5, HIGH);  
//}


void setup()

{
Serial.begin(115200);
//put your setup code here,to run once;

pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
//pinMode(led5, OUTPUT);
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

One_LED();
Serial.println("One_LED ON");

}

else if (cont == 2)

{

Two_LED();
Serial.println("TWO_LED ON");


}

else if (cont == 3)
{

Three_LED();
Serial.println("Three_LED ON");


}

else if (cont == 4)

{

Four_LED();
Serial.println("Four_LED");

}
//else if (cont == 5)
//
//{
//
//FIVE_LED();
//Serial.println("ALL_ON ");
//}
}
