// For wifi featuring and web access
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

// all below libray are for oled display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

//defined pins
#define pressing_pin 15

int count = 0; // flag for reseting
int pressing = 0;
void setup()
{ 
  count = 0;
  pinMode(pressing_pin, INPUT);
 
  
  //Oled Display setup code below
  Wire.begin(2,0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000); // Pause for 2 seconds  
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.setTextColor(WHITE);

  Serial.begin(9600); // always use after wire.begin because otherwise its not working (my own research(Subham deb) )
  Serial.println("connection is okay");

  
  // if does not connected to old network its run
  if(WiFi.status() != WL_CONNECTED){
      Serial.println("create own access point");
      own_accessPoint();
      delay(3000);



//     //auto connect code bellow
//   WiFiManager wifiManager;
//   //
//   display.clearDisplay();
//   display.setCursor(0,20);
//   display.print("creating access point");
//   display.display();
//   
//   wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
//   
//   display.println("deb connect and open 10.0.1.1");
//   display.display();
//   
//   wifiManager.autoConnect("D3B Connect");
//   Serial.println("connected");

    }
} // end setup function

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
        
        display.clearDisplay();
        display.setCursor(0,20);
        display.print(payload);
        display.display();
      }
     else{
        Serial.println("no response from link server");
        display.clearDisplay();
        display.setCursor(0,20);
        display.print("server doesn't response");
        display.display();
      
      }
      http.end();
  }

    count++;
    display.setCursor(0,40);
    display.print(count);
    display.display();
    Serial.println(count);
  delay(5000);
  pressing = digitalRead(pressing_pin); // GPIO 1 pin value thats attached to a button

  //if button is pressed then if function will run
  if(pressing){
    Serial.println("button is pressed");
     WiFi.disconnect();
     setup();
    }
    
}


void own_accessPoint(){

     //auto connect code bellow
   WiFiManager wifiManager;
   //
   display.clearDisplay();
   display.setCursor(0,20);
   display.print("creating access point");
   display.display();
   
   wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
   
   display.println("deb connect and open 10.0.1.1");
   display.display();
   
   wifiManager.autoConnect("D3B Connect");
   Serial.println("connected");
   
  }
