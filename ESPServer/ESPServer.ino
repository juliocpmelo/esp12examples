/*
Adapted from https://techtutorialsx.com/2018/06/02/esp8266-arduino-socket-server/
*/

#include "ESP8266WiFi.h"
 
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPass";
 
WiFiServer wifiServer(9999);
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        /*writes back to the client*/
        line[line.size()-1] = '\0'; //removes '\n' from response
	client.print(line);
      }
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
