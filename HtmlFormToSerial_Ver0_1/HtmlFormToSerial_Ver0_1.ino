#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String responseHTML = ""
                      "<!DOCTYPE html>"
                      "<html>"
	"<head>"
		"<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>"
		"<title>DataFormToSerial</title> "
		"<style type='text/css'> body,td,th { color: #036; } body { background-color: #999; overflow-x: hidden;} </style>" 
	"</head>"
	"<body> "
		"<br>"
		"<form action='config' method='get' target='pantalla' style='float: left'>"
			"<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:130px; padding:10px; margin: 5px;'>"
				"<legend><strong>Send Data to Serial</strong></legend>"
				"Data: <br> <input name='data' type='text' size='15'/> <br><br>"
				"<input type='button' value='Send' />"
			"</fieldset>"
		"</form>"
		"<iframe id='pantalla' name='pantalla' src='' width=900px height=400px frameborder='0' scrolling='no'></iframe>"
    "</body>"
"</html>";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Send Data to Serial");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
