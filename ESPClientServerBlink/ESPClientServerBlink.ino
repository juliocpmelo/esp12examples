/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/


#include <ESP8266WiFi.h>

char *ssid = "nome da rede";
char *password = "senha";

IPAddress server_addr(192,168,1,10);


void setup() 
{
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  /*connect to WiFi*/
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado à Wifi");
  Serial.print("Meu Ip é: ");
  Serial.println(WiFi.localIP());
}

void loop() {
WiFiClient client;

  Serial.printf("\n[Connecting... ");
  if (client.connect(server_addr, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print("ola!");

    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);

}
