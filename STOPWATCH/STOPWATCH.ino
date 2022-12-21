

/*
   Project:     Stopwatch with Arduino Nano
   Hardware:    ESP32 - 8 Dig x 7 Seg LED Display
   Revision:    1.2
   Date:        08.feb.2022
      
*/

#include <LedControl.h>       // Library for LED control with MAX72XX
#include <Bounce2.h>          // Library for Bounce of switches

/*
  Pins of Arduino Nano for LedControl:
  Pin #7 is connected to DataIn (DIN)
  Pin #8 is connected to CLK (CLK)
  Pin #9 is connected to LOAD (CS)
*/

// LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = (12, 13, 25, 26);

long tn, lastTime, diffTime, deltaT;
int milhar, centena, dezena, unidade;
int milhar1, centena1, dezena1, unidade1;

byte pinStartStop = 18;        // Start-Stop Pin
byte pinLapse = 19;            // Time Lapse Pin

bool statusSwitch1 = false;

Bounce SW1 = Bounce();        // Define Bounce to read StartStop switch
Bounce SW2 = Bounce();        // Define Bounce to read Lapse switch


void setup() {

  pinMode (pinStartStop, INPUT_PULLUP);
  pinMode (pinLapse, INPUT_PULLUP);

  // After setting up the button, setup the Bounce instance
  SW1.attach(pinStartStop);   // Sets the pin (Internal Pull-Up)and matches the internal state to that of the pin
  SW1.interval(4);            // Sets the debounce time in milliseconds
  SW2.attach(pinLapse);
  SW2.interval(4);

  lc.shutdown(0, false);      // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 3);      // Set the brightness of display between 0 and 15
  lc.clearDisplay(0);         // Clear the display

  lc.setDigit(0, 7, 0, true);
  lc.setDigit(0, 6, 0, false);
  lc.setDigit(0, 5, 0, true);
  lc.setDigit(0, 4, 0, false);

  lc.setDigit(0, 3, 0, false);
  lc.setDigit(0, 2, 0, true);
  lc.setDigit(0, 1, 0, false);
  lc.setDigit(0, 0, 0, false);

}


void loop() {

  SW1.update();   // Start-Stop

  if (SW1.fell()) {
    statusSwitch1 = !statusSwitch1;
  }

  if (statusSwitch1 == true && tn <= 599900) {

    tn = millis() - deltaT;

    milhar = tn / 60000;
    centena = (tn / 10000) % 6;
    dezena = (tn / 1000 ) % 10;
    unidade = (tn / 100) % 10;

    lc.setDigit(0, 7, milhar, true);
    lc.setDigit(0, 6, centena, false);
    lc.setDigit(0, 5, dezena, true);
    lc.setDigit(0, 4, unidade, false);
  }

  else {

    deltaT = millis() - tn;

    if (tn > 599900) {        // Overflow Warning for Stopwatch: "----"
      lc.setRow(0, 7, 1);
      lc.setRow(0, 6, 1);
      lc.setRow(0, 5, 1);
      lc.setRow(0, 4, 1);
    }

  }


  SW2.update();   // Lap Time

  if (SW2.fell()) {

    diffTime = tn - lastTime;
    lastTime = tn;

    milhar1 = diffTime / 10000;
    centena1 = (diffTime / 1000) % 10;
    dezena1 = (diffTime / 100) % 10;
    unidade1 = (diffTime / 10) % 10;

    lc.setDigit(0, 3, milhar1, false);
    lc.setDigit(0, 2, centena1, true);
    lc.setDigit(0, 1, dezena1, false);
    lc.setDigit(0, 0, unidade1, false);

    if (diffTime > 99990) {   // Overflow Warning for Lap Time: "----"
      lc.setRow(0, 3, 1);
      lc.setRow(0, 2, 1);
      lc.setRow(0, 1, 1);
      lc.setRow(0, 0, 1);
    }

  }

}
