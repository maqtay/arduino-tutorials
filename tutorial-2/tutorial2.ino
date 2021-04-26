class Button {
  private: 
  	int pin;
  	bool pressed;
  public: 
  	Button(int activePin, bool isPressed) {
    	pin = activePin;
    	pressed = isPressed;
  	};

  	int getPin(){
  		return pin;
  	};
  
  	bool isPressed() {
  		return pressed;
  	};
  
  	void setPressed(bool isPressed) {
    	pressed = isPressed;
  	};
};

int numberTables[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};
				   //A,B,C,D,E,F,G	
int segmentPins[] = {7,8,2,3,4,6,5};
int onesDigit = 9, tensDigit = 10;

Button incButton(13, false);
Button decButton(11, false);
Button ctrlButton(12, true);

Button buttons[] = {incButton, decButton, ctrlButton};

float counter = 0.0;
bool enablePotens = false;
int oldPotenValue = 0;
bool firstPotenValue = true;
short int systemActive = 1;
int tolerance = 10;

void setup() {
  Serial.begin(9600);
  for (int pin : segmentPins) pinMode(pin, OUTPUT);
  for (Button button : buttons) pinMode(button.getPin(), INPUT);

  pinMode(tensDigit, OUTPUT);
  pinMode(onesDigit, OUTPUT);

}

void loop() {
  Serial.print("Counter: ");
  Serial.println(counter);
  int tens = (int) counter / 10;
  int ones = (int) counter % 10;

  digitalWrite(tensDigit, LOW);
  digitalWrite(onesDigit, HIGH);

  turnOnSegments(ones);
  delay(10);

  for (int pin : segmentPins) digitalWrite(pin, LOW);
  
  digitalWrite(tensDigit, HIGH);
  digitalWrite(onesDigit, LOW);
  
  turnOnSegments(tens);
  delay(10);

  for (int pin : segmentPins) digitalWrite(pin, LOW);

  float velocity = (float) analogRead(0)/5000.0;
  checkButton(velocity);
  potentiometerCtrl(analogRead(1), velocity);
}

void turnOnSegments(int value) {
  for(int i=0; i<sizeof(segmentPins)/2; i++) digitalWrite(segmentPins[i], numberTables[value][i]);
}

void checkButton(float velocity) {
  if(digitalRead(incButton.getPin())) {
  	incButton.setPressed(true);
    decButton.setPressed(false);
    enablePotens = false;
  }
  if(digitalRead(decButton.getPin())) {
  	decButton.setPressed(true);
    incButton.setPressed(false);
    enablePotens = false;
  }

  if(digitalRead(ctrlButton.getPin()) && !systemActive)
  	ctrlButton.setPressed(!ctrlButton.isPressed());

  systemActive = digitalRead(ctrlButton.getPin());
  
  if(ctrlButton.isPressed() && !enablePotens) {
    if(incButton.isPressed()) {
      if(counter > 99.9) 
        counter = 0;
      counter += velocity;
    } else if(decButton.isPressed()){
      if (counter < 0)
      	counter = 99.9;      
      counter -= velocity;
    }
  }
}

void potentiometerCtrl(int value, float velocity) {
  if (firstPotenValue) {
    oldPotenValue = value;
    firstPotenValue = false;
  }

  int diff = abs(value - oldPotenValue);

  if (diff > tolerance) {
  	oldPotenValue = value;
    enablePotens = true;
  }

  if (enablePotens && ctrlButton.isPressed()) {
    if(value < 512){
      if(counter > 99.9) 
        counter = 0;
      counter += velocity;
    } else if (value > 511) {
      if (counter < 0)
        counter = 99.9;
      counter -= velocity;	
    } 
  }
}