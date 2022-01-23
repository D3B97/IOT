#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "DEB";  //ENTER YOUR WIFI SETTINGS
const char *password = "deb123456";

String postData;
int counter = 0;
void setup(){
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print("*");
    }
    Serial.println("");
    Serial.println("connected succesfully to router wifi");
    Serial.print("ESP8266 ip is:");
    Serial.println(WiFi.localIP());
}

void loop(){
    if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;


    
    http.begin(client,"http://192.168.0.143:3030/other");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    postData = "Count : " + counter ;
    
    int httpCode = http.POST(postData);
    if(httpCode > 0){
        String payload = http.getString();
        Serial.println(payload);
      }
     else{
        Serial.println("no response from link server");
      
      }
      http.end();
  }
  counter++;
  delay(5000);
}
