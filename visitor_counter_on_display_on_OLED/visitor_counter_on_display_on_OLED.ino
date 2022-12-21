//WELCOME TO JCBRO LABS 
//PLEASE SUBSCRIBE TO OUR YOUTUBE CHANNEL IF YOU R INTERESTED IN EMBEDDED SYSTEM
//OUR YOUTUBE CHANNEL NAME IS EMBEDDED GARAGE 
//SO PLEASE VISIT ONCE TO OUR CHANNEL
//LETS START TO THE PROJECT

#include <LiquidCrystal.h>
LiquidCrystal lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

#define in 14    //for enter
#define out 19  //for exit 
#define led 2   //your output pin(like bulb,fan...etc)

int count=0;

void IN()
{
    count++;
    lcd.clear();
    lcd.print("Person In Room:");
    lcd.setCursor(0,1);
    lcd.print(count);
    Serial.println("person in room:");
    Serial.println(count);
    delay(1000);
}

void OUT()
{
  count--;
   lcd.clear();
    lcd.print("Person In Room:");
    lcd.setCursor(0,1);
    lcd.print(count);
    Serial.println("person in room:");
    Serial.println(count);
    delay(1000);
}

void setup()
{
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.print("Visitor Counter");
  Serial.println("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(led, OUTPUT);
  lcd.clear();
  lcd.print("Person In Room:");
  lcd.setCursor(0,1);
  lcd.print(count);
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
     lcd.clear();
    digitalWrite(led, LOW);
     lcd.clear();
    lcd.print("Nobody In Room");
    lcd.setCursor(0,1);
    lcd.print("Light Is Off");
    Serial.println("Nobody In Room,Lights Off");
    Serial.print("");
    delay(500);
  }  
  else{
    digitalWrite(led, HIGH);
}
}
