#include <SoftwareSerial.h>
SoftwareSerial bluetoothSerial(32,33); // HERE RX=32 & TX=33;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("HC-05 AT Commands");
Serial.println("Function                | Command          | Response        | Parameter");
Serial.println("Test                    | AT               | OK              | None");
Serial.println("NAME                    | AT+NAME?         | +NAME:HC-05,OK  | HC-05 (Default)");
Serial.println("Password                | AT+PSWD?         | +PSWD:1234,OK   | 1234 (Default)");
Serial.println("Change Name             | AT+NAME = <name> | OK              | None");
Serial.println("Change Password         | AT+PSWD = <pswd> | OK              | NONE");
Serial.println("UART                    | AT+UART?         | +UART:38400,0,0 | 38400 (Default)");
Serial.println("Connection mode         | AT+CMODE?        | +CMOD:<cmod>    | 0 (Default)");
Serial.println("Connection mode set     | AT+CMODE=<cmode> | OK              | (0 (Connect to a specified address)) >> (1 (Connect to any available address))");
Serial.println("Find Address            | AT+ADDR?         | +ADDR:<addr>,OK | NONE");
Serial.println("Connect to Address      | AT+BIND=<addr>   | OK              | Replace the : with ,");
Serial.println("Reset Device            | AT+RESET         | OK              | None");
Serial.println("Restore factory Default | AT+ORGL          | OK              | None");
Serial.println("");
Serial.println("Enter AT commands to start:");
bluetoothSerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
// Keep reading from HC-05 and send to Arduino Serial Monitor
  if (bluetoothSerial.available())
    Serial.write(bluetoothSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
   bluetoothSerial.write(Serial.read());
}
