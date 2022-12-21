int Pin = 34;
int RCValue =0;

void setup(void) {
  pinMode(Pin, INPUT);
  Serial.begin(115200);
   delay(1000);
}
void loop(void) {
  // read the input on analog pin 34:
  RCValue = analogRead(Pin);
//  Serial.print("RCValue:");
  Serial.println(RCValue);
  delay(100);
}
