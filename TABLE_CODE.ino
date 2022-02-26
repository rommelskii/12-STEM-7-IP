#include <LiquidCrystal_I2C.h>
#include <dht.h>
LiquidCrystal_I2C lcd(0x27,16,2);  
dht DHT;

void homeMenu(int x) {
  switch (x) {
    case 1: 
      lcd.setCursor(0,0);
      lcd.print("[Temp]");
      lcd.setCursor(7,0);
      lcd.print("LED");
      lcd.setCursor(1,1);
      lcd.print("Sanitize");
      break;  
    case 2: 
      lcd.setCursor(1 ,0);
      lcd.print("Temp");
      lcd.setCursor(6,0);
      lcd.print("[LED]");
      lcd.setCursor(1 ,1);
      lcd.print("Sanitize");
      break;
    case 3: 
      lcd.setCursor(1,0);
      lcd.print("Temp");
      lcd.setCursor(7,0);
      lcd.print("LED");
      lcd.setCursor(0,1);
      lcd.print("[Sanitize]");
      break;  
  }
}

void tempMenu(int temp) {
      lcd.setCursor(0,0);
      lcd.print("Desk Temp:");
      lcd.setCursor(11,0);
      lcd.print(temp);
      lcd.setCursor(9, 1);
      lcd.print("[Back]");
      return;      
  }

void ledMenu (int red, int blue, int green, int a) {
  switch (a) {
    case 1: 
      lcd.setCursor(0,0); 
      lcd.print("[R]");
      lcd.setCursor(5,0); 
      lcd.print("G");
      lcd.setCursor(10,0); 
      lcd.print("B");
      lcd.setCursor(0,1);
      lcd.print(red);
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(10,1);
      lcd.print(blue);
      break;
    case 2:
      lcd.setCursor(0,0); 
      lcd.print("R");
      lcd.setCursor(5,0); 
      lcd.print("[G]");
      lcd.setCursor(10,0); 
      lcd.print("B");
      lcd.setCursor(0,1);
      lcd.print(red);
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(10,1);
      lcd.print(blue);
      break;
    case 3:
      lcd.setCursor(0,0); 
      lcd.print("R");
      lcd.setCursor(5,0); 
      lcd.print("G");
      lcd.setCursor(10,0); 
      lcd.print("[B]");
      lcd.setCursor(0,1);
      lcd.print(red);
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(10,1);
      lcd.print(blue);
      break;
    case 4: 
      lcd.setCursor(0,0);
      lcd.print("[Back]");
      break;      
  }
}
void ledRedAdjust(int red, int green, int blue, int c) {
  switch (c) {
    case 2:
      lcd.setCursor(0,0); 
      lcd.print("R");
      lcd.setCursor(5,0); 
      lcd.print("G");
      lcd.setCursor(10,0); 
      lcd.print("B");
      lcd.setCursor(0,1);
      lcd.print("[");
      lcd.setCursor(1,1);
      lcd.print(red);
      lcd.setCursor(4,1);
      lcd.print("]");
      lcd.setCursor(6,1);
      lcd.print(green);
      lcd.setCursor(11,1);
      lcd.print(blue);
      break;
      
  }
      return;
}
  


void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(12, HIGH);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
//declarations 
  int chk = DHT.read11(3);
  int pinStatus1 = digitalRead(1);
  int pinStatus2 = digitalRead(2); 
  int left = digitalRead(5);
  int right = digitalRead(4);
  int btnClk = digitalRead(6); 
  static int deskTemp;
  static int counter = 1; 
  static int clkCounter = 0;
  static int ledCounter = 1;
  static int ledAdjCounter = 1;  
  static int redVal = 255;
  static int greenVal = 255;
  static int blueVal = 255; 
  
//rgb
  analogWrite(A0, redVal);
  analogWrite(A1, greenVal);
  analogWrite(A2, blueVal);
   
//constraints
  counter = constrain(counter, 1, 3);
  ledCounter = constrain(ledCounter, 1, 4);

//sensor setup
  deskTemp = DHT.temperature;

//diagnostics
 /* Serial.println(counter);
  Serial.println(btnClk);
  Serial.println(clkCounter);
  Serial.println(ledCounter);
 */
  Serial.println(clkCounter);

//menu controls
  if (right == HIGH && clkCounter == 0 && ledCounter > 0) {
    counter++;
    lcd.clear();
  } else if (left == HIGH && clkCounter == 0 && ledCounter > 0) {
    counter--;
    lcd.clear();
  }

  if (btnClk == 1) {
    lcd.clear();
  }
  
//home and temp transitions
  if (btnClk == 1 && counter == 1 && clkCounter != 1) {
    clkCounter = clkCounter + 1;
  } else if (btnClk == 1 && counter == 1 && clkCounter == 1) {
    clkCounter = clkCounter - 1; 
  }
  if (btnClk == 1 && counter == 2 && clkCounter != 2) {
    clkCounter = clkCounter + 2;
  }
    else if (btnClk == 1 && counter == 2 && clkCounter == 2 && ledCounter == 4) {
    clkCounter = clkCounter - 2;
    ledCounter = ledCounter - 3;  
  }

//led menu transitions
  if (counter == 2 && clkCounter == 2 && left == HIGH) {
    ledCounter--;
    lcd.clear(); 
  } else if (counter == 2 && clkCounter == 2 && right == HIGH) {
    ledCounter++;
    lcd.clear();
  }

  
//home menu
if (clkCounter == 0) {
homeMenu(counter);
}
//temp menu
if (clkCounter == 1) {
  tempMenu(deskTemp);
}
//led menu
if (clkCounter == 2 && ledAdjCounter < 2) {
  ledMenu(redVal, greenVal, blueVal, ledCounter);
}

delay(100);
}
