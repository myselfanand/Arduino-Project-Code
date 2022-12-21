int pin1 = 32;
int pin2 = 33;


void setup ()
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  Serial.begin(115200);
}


void loop ()
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  Serial.println("move forward");
delay(5000);

digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  Serial.println("move backward");
delay(5000);

  
}
