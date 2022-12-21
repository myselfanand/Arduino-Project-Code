#define x 32
#define y 33
#define z 34

     
int x_val;
int y_val;
int z_val;



void setup () {
  Serial.begin(115200);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);
  
}


void loop () {
  x_val = analogRead(x);
  y_val = analogRead(y);
  z_val = analogRead(z);

  Serial.print("X: ");
  Serial.println(x_val);
  Serial.print("Y: ");
  Serial.println(y_val);
  Serial.print("Z: ");
  Serial.println(z_val);
  Serial.println();
  Serial.println("................");
  Serial.println();
  delay(500);
  
}
