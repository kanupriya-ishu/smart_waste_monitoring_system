#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>
// defines variables
const int trigPin1 = D5;
const int echoPin1 =D6;
const int trigPin2 = D7;
const int echoPin2 = D8;
long duration1,duration2;
int distance1,distance2;
int percent1,percent2;
WiFiClient client;
WiFiServer server(80);
const char* MY_SSID = "TP-Link";
const char* MY_PWD = "pr@s@d9020";
const char* TS_SERVER = "api.thingspeak.com";
String TS_API_KEY ="ZPSRGPO6KWC3D7BG";

//Wi-fi connectivity 

void connectWifi()  //connecting the WiFI via NodeMCU 
{
 Serial.begin(115200);
 Serial.print("Connecting to "+ *MY_SSID);
 WiFi.begin(MY_SSID, MY_PWD);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay(1000);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi Connected");
 Serial.println("");
 server.begin();
 Serial.println("Server started");
 Serial.print("Use this URL to connect: ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}

