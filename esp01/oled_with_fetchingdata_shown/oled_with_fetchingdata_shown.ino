#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     1

// wifi setup
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



const char* ssid = "DEB"; //Enter SSID
const char* password = "deb123456"; //Enter Password



void setup() 
{
Wire.begin(2,0);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
delay(2000); // Pause for 2 seconds  
display.setTextSize(1);
display.setCursor(0, 0);
display.setTextColor(WHITE);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) 
 {
   delay(500);
   display.print("!");
   display.display();
 }
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(10, 10);
  display.print("wifi connect");
  display.display();
  delay(1000);
  display.clearDisplay();

}
void loop()
{
  
    if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client,"http://www.randomnumberapi.com/api/v1.0/random?min=100&max=1000&count=5");
    int httpCode = http.GET();
    if(httpCode > 0){
        String payload = http.getString();
        display.setTextSize(3);
        display.setCursor(0, 10);
        display.print(payload);
        display.display();
      }
     else{
        display.println("no response from link server");
        display.display();
      
      }
      http.end();
  }
   delay(5000);
  display.clearDisplay();
  
  
  
  }
