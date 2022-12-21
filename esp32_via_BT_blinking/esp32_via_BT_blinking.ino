#include<BluetoothSerial.h>
BluetoothSerial SerialBT;

int received;
char receivedChar;

const char turnON = 'a';
const char turnOFF = 'b';

const int LEDpin = 14;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  Serial.println("the device is started, now you can pair with bluettooth");
  Serial.println("to turn On send a");
  Serial.println("to turn OFF send b");

  pinMode(LEDpin, OUTPUT);
  
}

void loop()
{
  receivedChar = (char)SerialBT.read();

  if(Serial.available()){
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    SerialBT.print("Received");
    SerialBT.print(receivedChar);
    Serial.print("Received");
    Serial.println(receivedChar);

    if(receivedChar ==turnON)
    {
      SerialBT.print("LED ON");
      Serial.println("LED ON");
      digitalWrite(LEDpin, HIGH);
    }
  }
 if(receivedChar ==turnOFF)
    {
      SerialBT.print("LED OFF");
      Serial.println("LED OFF");
      digitalWrite(LEDpin, LOW);
    }
}
