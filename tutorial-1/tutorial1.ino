// buton ve ledlerin kaç adet olacağını global olarak tanımladık
#define LedsNumber 5
#define ButtonsNumber 3

short int leds[LedsNumber] = {13, 12, 11, 10, 9};
short int buttons[ButtonsNumber] = {7, 4, 2};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<LedsNumber; i++) pinMode(leds[i], OUTPUT);
  for (int i = 0; i<ButtonsNumber; i++) pinMode(buttons[i], INPUT); 
}

void loop() {
  // hangi butan tıklandığını anlamamızı sağlar
  for (int i = 0; i<ButtonsNumber; i++) {
    int buttonState = digitalRead(buttons[i]);
    if(buttonState == HIGH) {
    	startTheCircuit(i);
   		continue;
   	}
  }
}

// hangi butona tıklanınca ne yapması gerektiğini belirtiriz
void startTheCircuit(int buttonIndex) {
  switch (buttonIndex) {
  	case 0:
    	turnOnTheLedsForFirst();
    	break;
    case 1:
        turnOnTheLedsForScnd();
    	break;
    case 2:
    	turnOnTheLedsForThrd();
    	break;
    default:
    	break;
  }
  turnOffTheLeds();
  return;
}

// tüm ledleri söndürür
void turnOffTheLeds() {
	for(int i=0; i<LedsNumber; i++) digitalWrite(leds[i], LOW);
	return;
}

// baştan başlayıp sona doğru ledleri yakar
void turnOnTheLedsForFirst() {
  	for (int i=0; i<LedsNumber; i++) {
    	delay(500);
  		digitalWrite(leds[i], HIGH);
   		delay(500);
  	}
	return;
}

// sondan baslayıp başa doğru ledleri yakar
void turnOnTheLedsForScnd(){
	for (int i=4; i>=0; i--) {
    	delay(500);
  		digitalWrite(leds[i], HIGH);
   		delay(500);
  	}
}

// Ledleri ile bir flash etkisi verecek şekilde yakıp söndürür
void turnOnTheLedsForThrd() {
	for (int i=0; i<10; i++) {
      	delay(500);
    	for (int j=0; j<LedsNumber; j++){
      		digitalWrite(leds[j], HIGH);
      	}
        delay(500);
      	turnOffTheLeds();
  	}
  	return;
}
