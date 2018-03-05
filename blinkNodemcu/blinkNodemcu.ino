
#include <ESP8266WiFi.h>

int stabilize = 0;
int samples[100];
bool firstSample=true, secondSample =false, waitForCrossing = false, heartBeatStabilize = true;
int firstBeatTime = 0, beatTimeDiff = 0;
float bpm = 0;

char *ssid = "Bjinhos AP";
char *password = "udtqcssondodt";


/*send things to dweet*/
void sendToDweet() {
  WiFiClient nodeClient;
  const char * server = "dweet.io";

  if (nodeClient.connect(server, 80)) {
    String url = "/dweet/for/julio-heart?";
    url += "bpm=";
    url += bpm;
  
    nodeClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" + 
                 "Connection: close\r\n\r\n");
  }
  else{
    Serial.println("Connection with Dweet.io failed");
  }
}

void setup() 
{
  
  Serial.begin(115200);
  pinMode(A0, INPUT);

  /*connect to WiFi*/
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("my Ip is: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  delay(50);
  maxDetection(analogRead(A0));

  /*debug purposes*/
  Serial.println(samples[4]);
  //Serial.print(",");
  //Serial.print(stabilize);
  //Serial.print(",");
  //Serial.println(bpm);

  //sendToDweet();
}

void maxDetection(int analogReading){

   for (int i= 0; i< 3; i++)
    samples[i] = samples[i+1];
   samples[4] = analogReading;

   int maxSamples = 0;
   /*check if sensor has stoped on 1024 on the last 11 samples*/
   for (maxSamples = 0; maxSamples< 5; maxSamples++)
    if(samples[maxSamples] != 1024)
      break;

   /*user has removed finger from sensor*/
   if(maxSamples == 5){
      bpm = 0;
      heartBeatStabilize = false;
      waitForCrossing = false;
      stabilize = 1000; //debug
   }
  
   if(waitForCrossing){
    if(analogReading > 900){
      stabilize = 0;
      return;
    }
    waitForCrossing = false;
   }
   stabilize = 1000;
   

   //when user puts the finger on the sensor
   if (analogReading <= 250 && !heartBeatStabilize){
      heartBeatStabilize = true;
      bpm = 0;
   }

   /*when user removes the finger from the sensor*/
   if(heartBeatStabilize && analogReading > 900){
      heartBeatStabilize = false;
      firstSample = true;
      secondSample = false;
   }

   if(!waitForCrossing){
     if(firstSample && analogReading > 900){
        firstBeatTime = millis();
        secondSample = true;
        firstSample = false;
        waitForCrossing = true;
     }
     else if(secondSample && analogReading > 900){
        secondSample = false;
        firstSample = true;
        beatTimeDiff = millis() - firstBeatTime;
        // beatTimeDiff / 1000 = period, 1/period = frequency Hz, Hz * 60 = bpm
        bpm = (1.0 / (beatTimeDiff / 1000.0)) * 60; 
        waitForCrossing = true;
     }
   }
}
