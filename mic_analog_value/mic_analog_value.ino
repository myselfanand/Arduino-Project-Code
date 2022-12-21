int pin = 14;
int micValue =0;

void setup()
{
  pinMode(pin,INPUT);
  Serial.begin(115200);
  delay(500);
}


void loop()
{
  micValue = analogRead(14);
  Serial.println(micValue);
  delayMicroseconds(100);
}
