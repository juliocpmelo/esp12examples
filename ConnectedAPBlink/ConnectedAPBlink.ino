#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "nome da rede";
const char *password = "senha";

ESP8266WebServer server(80);

/* Teste de mensagem, conecte no node e entre na página com o ip dele
 * via browser.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configurando AP");
  /* se você remover o parâmetro de password para criar uma rede aberta*/
  WiFi.softAP(ssid, password);


  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Meu endereço IP: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Iniciado Servidor http teste");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  server.handleClient();
}
