#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"

Talkie voice;

void setup() {
  pinMode(25,OUTPUT);
  digitalWrite(25, HIGH);
  delay(10);
  Serial.begin(9600);
  delay(500);
}
void loop() {
    voice.say(spPAUSE2);
    voice.say(sp2_DANGER);
    voice.say(sp2_DANGER);
    voice.say(sp3_STORM);
    voice.say(sp3_IN);
    voice.say(sp3_THE);
    voice.say(sp3_NORTH);
}
