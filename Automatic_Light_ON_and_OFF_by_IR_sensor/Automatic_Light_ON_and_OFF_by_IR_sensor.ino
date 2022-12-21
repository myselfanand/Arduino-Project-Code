//WELCOME TO JCBRO LABS 
//PLEASE SUBSCRIBE TO OUR YOUTUBE CHANNEL IF YOU R INTERESTED IN EMBEDDED SYSTEM
//OUR YOUTUBE CHANNEL NAME IS EMBEDDED GARAGE
//SO PLEASE VISIT ONCE TO OUR CHANNEL
//LETS START TO THE PROJECT

#define in 14    //for enter
#define out 19  //for exit 
#define led 2   //your output (like bulb,fan...etc)

int count=0;

void IN()
{
    count++;
    Serial.println("person in room:");
    Serial.println(count);
    delay(1000);
}

void OUT()
{
  count--;
    Serial.println("person in room:");
    Serial.println(count);
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
    Serial.println("Nobody In Room So,Light Is Off");
    Serial.print("");
    delay(500);
  }  
  else{
    digitalWrite(led, HIGH);
}
}
