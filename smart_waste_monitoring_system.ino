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
String TS_API_KEY ="6URW1ZLFFCW3NPTD";
