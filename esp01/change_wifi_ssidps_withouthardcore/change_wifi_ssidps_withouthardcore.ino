
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <WiFiManager.h>

//const char* ssid = "DEB"; //Enter SSID
//const char* password = "deb123456"; //Enter Password

// flagfor reset sets passwords
int count = 0;
 

void setup(void)
{ 
  count = 0;
  Serial.begin(115200);
  
  // Connect to WiFi
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) 
//  {
//     delay(500);
//     Serial.print("*");
//  }
//  
//  Serial.println("");
//  Serial.println("WiFi connection Successful");
//  Serial.print("The IP Address of ESP8266 Module is: ");
//  Serial.print(WiFi.localIP());// Print the IP address
  // end connect to wifi

  //auto connect to created_network code bellow
  WiFiManager wifiManager;
  wifiManager.setAPStaticIPConfig(IPAddress(11,0,1,1), IPAddress(11,0,1,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect("D3B Connect");
  Serial.println("connected");

  
}

void loop() 
{
  //  http://www.randomnumberapi.com/api/v1.0/random?min=100&max=1000&count=5
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client,"http://www.randomnumberapi.com/api/v1.0/random?min=100&max=1000&count=5");
    int httpCode = http.GET();
    if(httpCode > 0){
        String payload = http.getString();
        Serial.println(payload);
      }
     else{
        Serial.println("no response from link server");
      
      }
      http.end();
  }
  delay(5000);

  if(count == 5){
     WiFi.disconnect();
     setup();
    }
  count++;
  Serial.println(count);
}
