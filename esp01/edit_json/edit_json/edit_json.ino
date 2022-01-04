#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>





const char* ssid = "DEB"; //Enter SSID
const char* password = "deb123456"; //Enter Password



void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() 
{
//  http://www.randomnumberapi.com/api/v1.0/random?min=100&max=1000&count=5
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client,"https://api.openweathermap.org/data/2.5/weather?q=memari&appid=d3519e3d140c440e126ebedb08361889&units=metric");
    int httpCode = http.GET();
    if(httpCode > 0){
        String payload = http.getString();
        //converting to json
        char json[500];
        payload.replace(" ", "");
        payload.replace("\n","");
        payload.trim();
        payload.remove(0,1);
        payload.toCharArray(json,500);

        StaticJsonDocument<200> doc;
        deserializeJson(doc, json);

        int temp_cel = doc["base"];
        
        Serial.println(String(temp_cel));
      }
     else{
        Serial.println("no response from link server");
      
      }
      http.end();
  }
  delay(5000);
}
