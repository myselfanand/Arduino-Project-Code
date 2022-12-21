#include <WiFi.h>
#include <WebServer.h>
#include <Stepper.h>

const char *ssid = "JCBRO";
const char *password = "jcbro@321";

WebServer server(80);
const int CW =1; //where cw = clockwise
const int CCW =2;// ccw = counter clockwise
const int STOP =3;

int Pin1 = 13;//IN1 is connected to 13 
int Pin2 = 12;//IN2 is connected to 12  
int Pin3 = 14;//IN3 is connected to 14 
int Pin4 = 27;//IN4 is connected to 27 

long angles[] = {360, 270, 90, 20, 287};//angles of each push button
int directions[] ={CW, CCW, CW, CCW, CW};//direction of each push button
int speedFactors[] = {10, 1, 4, 10, 2};//speed for each push button
const String statusTitle[]={
            "Motor sent to ", 
            "Motor sent to ", 
            "Motor sent to ", 
            "Motor sent to ",
            "Motor sent to "};

const String directionTitle[]={"CW", "CCW"};
const String stopPushButtonTitle="STOP";
const String topTitle1 ="&deg; in ";
const String topTitle2 ="Speed factor: ";

const String topTitle3 ="Angle: ";
const String topTitle4 ="Direction: ";
const String topTitle5 =", Speed: ";
const String topTitle6 ="Send";
const String customMainTitle ="( C )Motor sent to ";

const int customValueButtonID=99;
const String motorStopped ="Motor Stopped";

int correction_CW = 150;
int correction_CCW = 150;


int poleStep = 0; 
long stepVale =0;
const int SPR=64*64;
long goToAngle=0;
int activeButton=0;
int speedValue =1;

int pole1[] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
int pole2[] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
int pole3[] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
int pole4[] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values


int count=0;
int  dirStatus = STOP;// stores direction status 3= stop (do not change)

void setup(void) {
  
 Serial.begin(9600);//initialize the serial monitor
 Serial.println("Control Stepper Motor");

 
 pinMode(Pin1, OUTPUT);//define pin for ULN2003 in1 
 pinMode(Pin2, OUTPUT);//define pin for ULN2003 in2   
 pinMode(Pin3, OUTPUT);//define pin for ULN2003 in3   
 pinMode(Pin4, OUTPUT);//define pin for ULN2003 in4    

     Serial.println("Connecting to ");
  Serial.println(ssid);

WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi Connected..!");
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/go", HTTP_GET, motorControl); 
  server.on("/stop",HTTP_GET, stopMotor); 
         
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}//end of setup


void loop(void) {
 
  server.handleClient();

    stepVale = (SPR * goToAngle)/360 ;
  
  
 if(poleStep>7){ 
   poleStep=0;
 } 
 if(poleStep<0){ 
   poleStep=7; 
 } 

        
 if(dirStatus ==CCW){ 
  
   poleStep++; 
   count++;   
   if(count+correction_CCW <= stepVale)
   {
    driveStepper(poleStep);      
   }else{
      driveStepper(8);  
   }
  
 }else if(dirStatus ==CW){ 
   poleStep--; 
   count++;   
   if(count+correction_CW <=stepVale)
   {
    driveStepper(poleStep);      
   }else{
      driveStepper(8);  
   }   
 }else{
  driveStepper(8);    
 }


  delay(speedValue);
  
   
}//end of loop


void motorControl() {

 for (byte i = 0; i < (sizeof(angles) / sizeof(angles[0])); i++) {
   if(server.arg("angle") == String(angles[i]) )
   {
      goToAngle =angles[i];
      dirStatus =directions[i];
      count =0;
      activeButton =i;   
      speedValue=speedFactors[i];
   }//if
 }//for

   if(server.arg("d").toInt() >0 )
   {
      goToAngle =server.arg("angle").toInt();
      dirStatus =server.arg("d").toInt();
      count =0;
      activeButton =customValueButtonID;   
      speedValue=server.arg("s").toInt();    
   }

  handleRoot();
  
}//motorControl end


void driveStepper(int c)
{
  
     digitalWrite(Pin1, pole1[c]);  
     digitalWrite(Pin2, pole2[c]); 
     digitalWrite(Pin3, pole3[c]); 
     digitalWrite(Pin4, pole4[c]);   
   
}//driveStepper end here


void stopMotor()
{
  
  dirStatus=STOP;
  handleRoot();
}//stopMotor()


void handleRoot() {
  
 String HTML ="<!DOCTYPE html>\
  <html>\
  <head>\
  \t\n<title>ESP32 Stepper Motor</title>\
  \t\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  \n<style>\
 \nhtml,body{\t\nwidth:100%\;\nheight:100%\;\nmargin:0}\n*{box-sizing:border-box}\n.colorAll{\n\tbackground-color:#90ee90}\n.colorBtn{\n\tbackground-color:#add8e6}\n.angleButtdon,a{\n\tfont-size:30px\;\nborder:1px solid #ccc\;\ndisplay:table-caption\;\npadding:7px 10px\;\ntext-decoration:none\;\ncursor:pointer\;\npadding:5px 6px 7px 10px}a{\n\tdisplay:block}\n.btn{\n\tmargin:5px\;\nborder:none\;\ndisplay:inline-block\;\nvertical-align:middle\;\ntext-align:center\;\nwhite-space:nowrap}\n";
   
  HTML +="</style>\n\n</head>\n\n<body style = background-color:AQUA; ALIGN=CENTER >\n<h1 style = color:RED>Control Stepper Motor Angle  </h1>\n"; // change the page header name

    if(dirStatus !=STOP && activeButton !=customValueButtonID ){

          HTML +="\n\t<h2><span style=\"background-color: #FFFF00\">";   
          HTML +=statusTitle[activeButton];    
          HTML +=String(angles[activeButton]);  
          HTML +=topTitle1;                        
          HTML +=directionTitle[directions[activeButton]-1]; //subtract 1 to get proper title   
          HTML +="</span></h2>\n";
          
          HTML +="\n\t<h2>";                                
          HTML +=topTitle2;          
          HTML +=String(speedFactors[activeButton]); 
          HTML +="<span style=\"background-color: #FFFF00\"> (";
          float  timeTakes =(float)speedFactors[activeButton] * float(angles[activeButton]) * ((float)4/(float)360);//calculat the time that takes to move to that angle 
          HTML +=String(timeTakes);                               
          HTML +=" seconds)";                     
          HTML +="</span></h2>\n";            
 
   }if(activeButton ==customValueButtonID ){

          HTML +="\n\t<h2><span style=\"background-color: #FFFF00\">";   
          HTML +=customMainTitle;    
          HTML +=String(goToAngle);  
          HTML +=topTitle1;                        
          HTML +=directionTitle[dirStatus-1]; //subtract 1 to get proper title   
          HTML +="</span></h2>\n";
          
          HTML +="\n\t<h2>";                                
          HTML +=topTitle2;          
          HTML +=String(speedValue); 
          HTML +="<span style=\"background-color: #FFFF00\"> (";
          float  timeTakes =(float)speedValue * float(goToAngle) * ((float)4/(float)360);//calculat the time that takes to move to that angle 
          HTML +=String(timeTakes);                               
          HTML +=" seconds)";                     
          HTML +="</span></h2>\n";            
 
   }else if(dirStatus ==STOP)
   {
    HTML +="\n\t<h2><span style=\"background-color: #FFFF00\">"; 
    HTML +=motorStopped; 
    HTML +="</span></h2>\n";          
   } 

        HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#";
        HTML +="f59898";//set the color of buttons if active or not
        HTML +="\t\"  href=\"/stop";               
        HTML +="\">";      
        HTML +=stopPushButtonTitle;//tilte on button
       HTML +="</a>\t\n\t</div>\n\n";   
 for (byte i = 0; i < (sizeof(angles) / sizeof(angles[0])); i++) {

        HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#";
        if(i ==activeButton)
        {
          HTML +="f59898";//set the color of buttons if active or not
        }else{
          HTML +="90ee90";//set the color of buttons if active or not
        }

        HTML +="\t\"  href=\"/go?";               
        HTML +="angle=";
        HTML +=angles[i];
        HTML +="\">";      
        HTML +=angles[i];//tilte on button

     HTML +="&deg; "; //degree symbol for HTML &deg;
     HTML +=directionTitle[directions[i]-1];
     HTML +="</a>\t\n\t</div>\n\n"; //degree symbol for HTML &deg;     
   }

  //custom angle
  HTML +="<form action=\"/go\" method=\"get\">\n";  

  HTML +="<label for=\"angle\">\n";
  HTML += topTitle3;  
  HTML +="</label> \n";  
  HTML +="<input type=\"text\" id=\"angle\" name=\"angle\" value=\"\n";
  HTML +=String(goToAngle); 
  HTML +="\"  maxlength=\"4\" size=\"4\"> \n";    

  HTML +="<input type=\"radio\" id=\"cw\" \n";
  if( dirStatus  ==1){
    HTML +="checked=\"checked\"";
  }
  HTML +=" name=\"d\" value=\"1\">\n";    
  HTML +="<label for=\"cw\">CW</label>\n"; 
  
  HTML +="<input type=\"radio\" id=\"ccw\" \n";
  if( dirStatus  ==2){
    HTML +="checked=\"checked\"";
  }
  HTML +=" name=\"d\" value=\"2\">\n";  
  HTML +="<label for=\"female\">CCW</label>\n";

  HTML +="<label for=\"spd\">\n";
  HTML +=topTitle5;
  HTML +="</label> \n";    
  HTML +="<input type=\"text\" id=\"spd\" name=\"s\" value=\"1\"  maxlength=\"2\" size=\"4\"><br>\n";
  
  HTML +="<input type=\"submit\" value=\"\n";  
  HTML +=topTitle6;
  HTML +="\">\n";     
  HTML +="</form> \n\n"; 

  HTML +="\t\n</body>\n</html>\n";
  server.send(200, "text/html", HTML);  
   
}//handleRoot()

void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  
}//end of handleNotFound()




            
