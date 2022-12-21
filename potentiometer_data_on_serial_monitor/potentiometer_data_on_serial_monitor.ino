int potPin = 14;

int potValue = 0;
float voltage;

void setup()
{
 Serial.begin(115200);
 delay(500);
}


void loop ()
{
  potValue = analogRead(potPin);
  voltage = potValue*(5.0/4095);
  Serial.println(voltage);
  delay(1000);
}
