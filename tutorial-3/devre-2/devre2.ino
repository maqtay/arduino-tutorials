#include <LiquidCrystal.h>
int light = 0;
float temp = 0.;
int gas = 0;

// R5, E, DB4, DB5, DB6, DB7 lcd 
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup()
{
  	pinMode(A0, INPUT);
  	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
  	lcd.begin(16, 2);
  	Serial.begin(9600);
}

void loop() {
  	float a = analogRead(A1);
	float temp = (((a*5)/1023)-0.5)*100;
  
  	light = analogRead(A2);
  	light = map(light, 6, 680, 0, 10);
    
    int gas = analogRead(A0);	
  	gas = map(gas, 300, 750, 0, 10);
  	Serial.println(gas);

  	lcd.setCursor(0, 0);
  	lcd.print("Temperature: ");
  	lcd.print(temp);
  	lcd.print(" C ");

  	lcd.setCursor(0, 1);
	
  	lcd.print("Light: ");
  	lcd.print(light);
  	
  	lcd.print(" Gas: ");
  	lcd.print(gas);
}