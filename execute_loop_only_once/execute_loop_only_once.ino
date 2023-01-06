// methode 1 to execute loop once
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

/*
// methode 2 to execute loop once
bool control_loop; // by default it is false; it u want u declare them, then it is as:- bool control_loop = false;
//bool control_loop = false;

void setup() {
  Serial.begin(115200);   // This initializes the Serial monitor
}

void loop() {
 if(!control_loop) 
  {
    Serial.print("hello, world!");  // Display on Serial monitor
    control_loop = true;
  }
}
*/
