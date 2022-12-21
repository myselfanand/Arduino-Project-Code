#define in 14    //for enter
#define out 19  //for exit 
#define led 2   //your output pin(like bulb,fan...etc)

int led1 = 25;
int led2 = 26;
int led3 = 27;
//int led4 = 23;

int count=0;

void IN()
{
    count++;
    Serial.println("person in room:");
    Serial.println(count);
    if (count >= 1){
     digitalWrite(led1,HIGH);
    }
    if (count >= 2){
     digitalWrite(led2,HIGH);
    }
    if (count >= 3){
     digitalWrite(led3,HIGH);
    }
//     if (count >= 4){
//     digitalWrite(led4,HIGH);
//    }
    
    delay(1000);
}

void OUT()
{
  count--;
    Serial.println("person in room:");
    Serial.println(count);
//    if (count<= 4){
//     digitalWrite(led4,LOW);
//    }
    if (count<= 3){
     digitalWrite(led3,LOW);
    }
    if (count<= 2){
     digitalWrite(led2,LOW);
    }
    if (count<= 1){
     digitalWrite(led1,LOW);
    }
    delay(1000);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(led, OUTPUT);
    pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
        pinMode(led3, OUTPUT);
   Serial.println("Person In Room:");
   Serial.println(count);
}

void loop()
{   
  if(digitalRead(in))
  IN();
  if(digitalRead(out))
  OUT();
  
  if(count<=0)
  {
    digitalWrite(led, LOW);
    Serial.println("Nobody In Room,Lights Off");
    Serial.print("");
    delay(500);
  }  
  else{
    digitalWrite(led, HIGH);
}
}
