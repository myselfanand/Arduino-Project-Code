
//transmiter code

//#include <SoftwareSerial.h>
//SoftwareSerial MyBlue(18,19);

#define x 32
#define y 33
//#define z 34


#define led1  =18;
#define led2 = 19;
#define led3 = 22;
#define led4 = 23;

int x_val =0;
int y_val =0;
//int z_val;

int x_val2 =0;
int y_val2 =0;
//int z_val2;

void setup () {
  Serial.begin(115200);
//  MyBlue.begin(38400);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
//  pinMode(z,INPUT);

  x_val2 = analogRead(x);
  y_val2 = analogRead(y);
//  z_val2 = analogRead(z);
}


void loop () {
  x_val = analogRead(x);
  y_val = analogRead(y);
  //z_val = analogRead(z);

int x_axis = x_val - x_val2;
int y_axis = y_val - y_val2;
//int z_axis = z_val - z_val2;

  if (y_axis >= 300)
  {
//    MyBlue.write("L");
    Serial.println("L");
  }
  else if (y_axis <= -300)
  {
//    MyBlue.write("R");
    Serial.println("R");
  }
  else if (x_axis >= 300)
  {
//    MyBlue.write("B");
    Serial.println("B");
  }
  else if (x_axis <= -300)
  {
//    MyBlue.write("F");
    Serial.println("F");
  }
  else 
  {
//    MyBlue.write("S");
//    Serial.println("S");
  }
  delay(500);
}
