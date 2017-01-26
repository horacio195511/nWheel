#include<SoftwareSerial.h>
#define sw_rx 4//connect this pin to TX on ESP
#define sw_tx 6//connect tis pin to RX on ESP

SoftwareSerial wifi(sw_rx, sw_tx); //接收，傳送
void sendCommand(String command, unsigned int waitTime);

void setup() {
  //Serial.begin(9600);
  wifi.begin(9600);
  
  /*Basic wifi and TCP/IP configuration*/
  sendCommand("AT+RST\r\n", 2000);
  sendCommand("AT+CWMODE=2\r\n", 1000);       //startLocalAP();
  sendCommand("AT+CIFSR\r\n", 1000);          //getIP() Address
  sendCommand("AT+CIPMUX=1\r\n", 1000);       //Start multi connection
  sendCommand("AT+CIPSERVER=1,80\r\n", 1000); //Start Server on port 80
}

void loop() {
  if (wifi.available()) {
    if (wifi.find("+IPD,")) {                //read buffer to +IPD
      delay(100);
      byte connID = wifi.read() - 48;        //read id, then transform ascll to number
      //build our webpage
      String HTML = "<!doctype html>";
      HTML +="<html><head>";
      HTML +="<title>aWHeel Consol</title></head>";
      HTML +="<body bgcolor=\"#000000\" text=\"#ffffff\">";
      HTML +="<font color=\"#00f00\" size=\"7\">";
      HTML +="TRAIN<br>";
      HTML +="</font>";
      HTML +="You are waiting for a train. A train will take you far away<br>";
      HTML +="You don't know where it wll reach<br>";
      HTML +="But it doesn't matter.<br>";
      HTML +="<font color=\"#ff0000\">";
      HTML +="Because we will go togather";
      HTML +="</font>";
      HTML +="</body></html>";

      //tell esp to SEND to data client with CIPSEND
      String cipSend = "AT+CIPSEND=";
      cipSend += connID;
      cipSend += ",";
      cipSend += HTML.length();
      cipSend += "\r\n";

      //Serial.println(cipSend);//debug usage
      //Serial.println(HTML);

      sendCommand(cipSend, 1000);
      sendCommand(HTML, 1000);

      //data has been send close connection
      String cipClose = "AT+CIPCLOSE=";
      cipClose += connID;
      cipClose += "\r\n";

      sendCommand(cipClose, 1000);
    }
  }
}



void sendCommand(String command, unsigned int waitTime) {
  String response = ""; //recieve the variable ESP GET
  wifi.print(command);
  unsigned long timeout = waitTime + millis();

  while (wifi.available() || millis() < timeout) {
    while (wifi.available()) {
      char c = wifi.read();
      response += c; //load char read from sw to responce
    }
  }
  //Serial.print(response);
}

