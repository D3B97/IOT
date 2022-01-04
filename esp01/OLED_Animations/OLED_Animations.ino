#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




void setup() 
{
Wire.begin(2,0);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
delay(2000); // Pause for 2 seconds  
display.clearDisplay();


display.setTextSize(1);
display.setCursor(0, 0);
display.setTextColor(WHITE);

display.print("Hello Worlld!");

display.display();
delay(10000);
display.clearDisplay();
 

}
void loop()
{
  
  display.print("Hello Worlld!");
  display.display();
  delay(10000);
  display.clearDisplay();
  display.print("Hello Subham");
  display.display();
  delay(10000);
  display.clearDisplay();
  
  
  }
