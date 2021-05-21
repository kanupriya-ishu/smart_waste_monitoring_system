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

//ULtrasonic sensor

long readUltrasonicDistance(int triggerPin, int echoPin)  //THis function reads the ultrasonic distance and garbage level in bin
 {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
  }


// Send data to ThingSpeak Server
void sendDataTS(void)  
{
	float cm1 = 0.01723 * readUltrasonicDistance(trigPin1,echoPin1);
	//int percent1 = map(cm1,9.8,0,0,100);
	int percent1 = 100 - (int)(cm1/9.8*100);
	float cm2 = 0.01723 * readUltrasonicDistance(trigPin2,echoPin2);
	//int percent2 = map(cm2,9.8,0,0,100);
	int percent2 = 100 - (int)(cm2/9.8*100);
	Serial.print("Percent_1: ");
	Serial.println(percent1);
	Serial.print("Percent_2: ");
	Serial.println(percent2);

	if (client.connect(TS_SERVER, 80))
	{
	String url = "/update?api_key=";
	url += TS_API_KEY;
	url += "&field1=";
	url += String(percent1);
	url += "&field2=";
	url += String(percent2);

	Serial.print("Requesting URL: ");
	Serial.println(url);

	// This will send the request to the server
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
			   "Host: " + TS_SERVER + "\r\n" + 
			   "Connection: close\r\n\r\n");
	delay(100);
	}
	client.stop();
}
