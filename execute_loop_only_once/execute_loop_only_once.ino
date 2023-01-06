int i = 0;

void setup() {
  Serial.begin(115200);   // This initializes the Serial monitor
}

void loop() {
 while(i == 0) {
    Serial.print("hello, world!");  // Display on Serial monitor
    i++;
  }
}
