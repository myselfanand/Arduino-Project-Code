const int buzzer = 13;  // Buzzer pin
int LED_BUILTIN = 2;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
}
 
void loop()
{
//  for(int i = 250; i > 0 ; --i)
//  Serial.println(i);
  {
    delay(500);
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  delay(500);
}
