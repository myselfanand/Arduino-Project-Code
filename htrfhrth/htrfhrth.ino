#define timeSeconds 5

// Set GPIOs for LED and PIR Motion Sensor
const int led = 2;
const int IRSensor = 34;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsobject() {
  Serial.println("HELLO!!!");
  digitalWrite(led, HIGH);
  startTimer = true;

  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(IRSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(IRSensor), detectsobject, RISING);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
// Current time
  now = millis();
// Turn off the LED after the number of seconds defined in the timeSeconds variable
 if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("BYE BYE...");
    digitalWrite(led, LOW);
    startTimer = false;
  }
}
