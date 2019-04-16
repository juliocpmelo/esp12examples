/*
!author Julio Melo
!brief this example shows how to connect ESP with an external server
       located on the server_addr address on port server_port. This example
       is meant to execute together with the pythonServer.py on this folder.
*/


#include <ESP8266WiFi.h>

char *ssid = "nome da rede";
char *password = "senha";

/*endereço do servidor*/
IPAddress server_addr(192,168,1,10);
int server_port = 9999;

void setup() 
{
  
  Serial.begin(115200);

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
  if (client.connect(server_addr, server_port))
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
