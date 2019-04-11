
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "nome da rede";
const char *password = "senha";

ESP8266WebServer server(80);

bool blink = false;

/* Teste de mensagem, conecte no node e entre na página com o ip dele
 * via browser.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
  blink = !blink;
}

void setup() {
  /*
   delay para evitar que a configuracao da porta serial aconteca
   antes do usuario ter tempo de ver a saida da porta
   */
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configurando AP");
  
 
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

  server.on("/", handleRoot);
  server.begin();
  /*
    funcao handleRoot eh chamada quando um cliente conecta no endereco
    do esp. Voce pode mudar esse codigo para /qualquercoisa, para chamar
    diferentes funcoes quando o cliente entra com o endereco 
    <ip>/qualquercoisa
  */
  Serial.println("Iniciado Servidor http");
  server.on("/", handleRoot);
  server.begin();
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
}

void loop() {
  /*
    precisamos chamar, obrigatoriamente essa funcao, caso contrario
    nossos handlers nao serao chamados quando houver conexao
  */
  server.handleClient();
  /*blink gourmet*/
  if(blink){
    if(digitalRead(D0) == HIGH)
      digitalWrite(D0, LOW);
    else
      digitalWrite(D0, HIGH);
    delay(200);
  }
}
