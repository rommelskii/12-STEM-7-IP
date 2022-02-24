#include <LiquidCrystal_I2C.h>
#include <dht.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
dht DHT;


void setup() {
  Serial.begin(9600);

  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
//declarations 
  int chk = DHT.read11(4);
  int pinStatus7 = digitalRead(7);
  int pinStatus8 = digitalRead(8);
  int btnClk = digitalRead(9); 
  static int deskTemp;
  static int counter = 1; 
  static int ledCounter = 0;
  static int clkCounter = 0; 
  static int redVal = 255;
  static int greenVal = 255;
  static int blueVal = 255; 
//rgb
  analogWrite(A0, redVal);
  analogWrite(A1, greenVal);
  analogWrite(A2, blueVal); 
//constraints
  counter = constrain(counter, 1, 3);
//  clkCounter = constrain(clkCounter, 0, 1);
//sensor setup
  deskTemp = DHT.temperature;

//menu controls
if (pinStatus8 == HIGH) {
    counter++;
    lcd.clear();
  } else if (pinStatus7 == HIGH) {
    counter--;
    Serial.println(counter);
    lcd.clear();
  }
  Serial.println(clkCounter);
  delay(150);
  if (btnClk == HIGH) {
    lcd.clear();
  }



  Serial.println(btnClk);
//home menu
  if (counter == 1 && btnClk != HIGH && clkCounter == 0 && ledCounter == 0) {
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("->Temp");
    lcd.setCursor(8,0); 
    lcd.print("LED");
    lcd.setCursor(0,1); 
    lcd.print("Sanitize");
  } else if (counter == 2 && btnClk != HIGH && clkCounter == 0 && ledCounter == 0) {
      lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Temp");
    lcd.setCursor(8,0); 
    lcd.print("->LED");
    lcd.setCursor(0,1); 
    lcd.print("Sanitize");
  } else if(counter == 3 && btnClk != HIGH && clkCounter == 0 && ledCounter == 0) {
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Temp");
    lcd.setCursor(8,0); 
    lcd.print("LED");
    lcd.setCursor(0,1); 
    lcd.print("->Sanitize");   
  }
//temp menu 
  if (counter == 1 && btnClk == HIGH) {
    clkCounter = clkCounter + 1; 
  }
  if (clkCounter == 1) {  
    lcd.setCursor(0,0);
    lcd.print("Desk Temp");
    lcd.setCursor(10, 0);
    lcd.print(deskTemp);
    lcd.setCursor(12,0);
    lcd.print("C");
  } else if (clkCounter == 2) {
    clkCounter = 0;
  }

//led menu 
  if (counter == 2 && btnClk == HIGH) {
    clkCounter = clkCounter + 3; 
  }
  if (clkCounter == 3) {  
    lcd.setCursor(0,0);
    lcd.print("R");
    lcd.setCursor(5, 0);
    lcd.print("G");
    lcd.setCursor(10,0);
    lcd.print("B");

    lcd.setCursor(0,1);
    lcd.print(redVal);
    lcd.setCursor(5,1);
    lcd.print(greenVal);
    lcd.setCursor(10,1);
    lcd.print(blueVal);
  } else if (clkCounter == 6) {
    clkCounter = 0;
  }

 

}
