#include<SPI.h>
#include<SD.h>
#include<FS.h>
 
File myfile;

void setup ()
{
  Serial.begin(115200);
  //initialization of SD card
  while(!SD.begin(5))
  {
    ;
  }
  Serial.println("Your SD card is ready to use");
  
  // Check to see if the file exists:
  if (SD.exists("biii_tech.txt")) {
    Serial.println("biii_tech.txt exists.");
  } else {
    Serial.println("biii_tech.txt doesn't exist.");
  }
  
  myfile = SD.open("biii_tech.txt",FILE_WRITE);
  if(myfile)
  {
    myfile.print("Biii_Tech NOIDA");
    Serial.println("data saved");
    myfile.close();
  }

  else{
    Serial.println("unable to open file");
  }
}

void loop()
{

}
