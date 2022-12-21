

// here is the code to display on web page server //


server.handleClient();
}
void handle_OnConnect(){


 server.send(200, "text/html", SendHTML(change a/c you));  
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float change a/c to you){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>changing here according to you</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>changing here according to you</h1>\n";


  ptr +="<p>potValue: ";
  ptr +=(String)potValue;
  ptr +="cm</p>";

 ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
