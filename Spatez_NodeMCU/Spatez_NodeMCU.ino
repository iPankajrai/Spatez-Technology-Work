#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
 
//Replace your wifi credentials here
const char* ssid     = "spatez";
const char* password = "spatez@2019";
 
//change your channel number here
unsigned long channel = 754932;
 
//1 is the  channel fields
unsigned int led1 = 1;

WiFiClient  client;
 
void setup()
{
  Serial.begin(115200);
  delay(100);
  
  pinMode(D1, OUTPUT);
  pinMode(D2,INPUT);
  digitalWrite(D1, 0);
  
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
 
}

 
void loop() 
{

  //get the last data of the fields
  int led_1 = ThingSpeak.readFloatField(channel, led1);
 
 
  if(led_1 == 1)
  {
    digitalWrite(D1, 1);
    Serial.println("D1 is On..!");
  }
  else if(led_1 == 0)
  {
    digitalWrite(D1, 0);
    Serial.println("D1 is Off..!");
  }
    
  Serial.println(led_1);
  delay(1000);
  
  int x=analogRead(D2);
  
  int temp= (x*500)/ 1024;
  Serial.println(temp);
  delay(1000);
  int temp = ThingSpeak.readFloatField(channel, temp);

 
}
