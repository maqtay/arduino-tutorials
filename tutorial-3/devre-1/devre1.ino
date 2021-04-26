short int pirPin = 2;
short int redLed = 4;
  
void setup() {
	pinMode(pirPin, INPUT);
  	pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(pirPin) == HIGH) {
    digitalWrite(redLed, HIGH);
  } else if(digitalRead(pirPin) == LOW) {
    digitalWrite(redLed, LOW);
  }
}