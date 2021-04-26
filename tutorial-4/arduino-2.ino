#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(7,6,5,4,3,2);

// 0 -> şifre al
// 1 -> doğru şifre
// 2 -> yanlış şifre
short int status = 0;

short int passLength = 0;
int pass[6] = {'1', '2', '3', '4', '5', '6'};
bool passStatus = true;
bool systemActive = true;
short int attempts = 0;

short int buzzer = 8;
short int pirPin = 9;
short int enginePin = 10;

Servo engine;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin, INPUT);

  lcd.begin(16,2);
  lcd.print("Enter Password!");
  lcd.setCursor(0,1);
}

void loop (){
  if (systemActive) {
    if (digitalRead(pirPin) == HIGH) {
      tone(buzzer, 262);   
    }
  }
  lcd.blink();
  if (status == 0) {
    // şifre gir
  	if (Serial.available() > 0) {
      int str = Serial.read();
      if (str != pass[passLength]) {
        passStatus = false;
      }
      lcd.write("*");
      passLength++;
      Serial.println(passStatus);
      if (passLength == 6 && passStatus) {
      	status = 1;
      } else if (passLength == 6 && !passStatus) {
      	status = 2;
      }
    }
  } else if (status == 1) {
  	// şifre doğru
    noTone(buzzer);
    delay(500);
    lcd.clear();
    lcd.print("Rigth password");
    lcd.setCursor(0,1);

    if (systemActive) {
      lcd.print("System inactive!");
      doorOpen();
    } else {
      lcd.print("System active!");
      doorOpen();
    }
	lastTouch();
    
  } else if (status == 2) {
  	// şifre yanlış
    tone(buzzer, 262);
    delay(250);
    lcd.clear();
	lcd.print("Wrong password!");
	lastTouch();
	noTone(buzzer);
  }
}

void lastTouch() {
  delay(1000);
  lcd.clear();
  lcd.print("Enter Password!");
  lcd.setCursor(0, 1);
  passLength = 0;
  passStatus = true;
  status = 0;
}

void doorOpen() {
  engine.attach(enginePin);
  if (systemActive) {
    engine.write(90);
  } else {
  	engine.write(-90);
  }
  delay(1000);
  systemActive = !systemActive;
}