

void setup() 
{
  
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  Serial.println("Intialize Blink");
}

void loop() 
{
	delay(1000);
	digitalWrite(D0, HIGH);
	delay(1000);
	digitalWrite(D0, LOW);
}

