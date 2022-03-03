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

void ledMenu (int red, int green, int blue, int a) {
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
      lcd.setCursor(15,1);
      lcd.print(">");
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
      lcd.setCursor(15,1);
      lcd.print(">");
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
      lcd.setCursor(15,1);
      lcd.print(">");
      break;
    case 4: 
      lcd.setCursor(0,0);
      lcd.print("[Back]");
      break;      
  }
}

void ledAdjustMenu(int red, int green, int blue, int counter) {
  switch (counter) {
    case 1: 
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
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(10,1);
      lcd.print(blue);
      lcd.setCursor(15,1);
      break;
    case 3: 
      lcd.setCursor(0,0); 
      lcd.print("R");
      lcd.setCursor(5,0); 
      lcd.print("G");
      lcd.setCursor(10,0); 
      lcd.print("B");
      lcd.setCursor(0,1);
      lcd.print(red);
      lcd.setCursor(4,1);
      lcd.print("[");
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(8,1);
      lcd.print("]");
      lcd.setCursor(10,1);
      lcd.print(blue);
      lcd.setCursor(15,1);
      break;
    case 5:
      lcd.setCursor(0,0); 
      lcd.print("R");
      lcd.setCursor(5,0); 
      lcd.print("G");
      lcd.setCursor(10,0); 
      lcd.print("B");
      lcd.setCursor(0,1);
      lcd.print(red);
      lcd.setCursor(5,1);
      lcd.print(green);
      lcd.setCursor(9,1);
      lcd.print("[");
      lcd.setCursor(10,1);
      lcd.print(blue);
      lcd.setCursor(13,1);
      lcd.print("]");     
      break; 
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
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
  int up = digitalRead(2);
  int down = digitalRead(1); 
  int btnClk = digitalRead(6); 
  int btnClk2 = digitalRead(6);
  static int deskTemp;
  static int counter = 1; 
  static int clkCounter = 0;
  static int ledCounter = 1;
  static int ledAdjCounter = 0;
  static int ledBuffer = 0;   
  static int redVal = 128;
  static int greenVal = 127;
  static int blueVal = 127; 
  
//rgb
  analogWrite(A0, redVal);
  analogWrite(A1, greenVal);
  analogWrite(A2, blueVal);
   
//constraints
  counter = constrain(counter, 1, 3);
  ledCounter = constrain(ledCounter, 1, 4);
  ledAdjCounter = constrain(ledAdjCounter, 0, 10);
  redVal = constrain(redVal, 127, 255);
  greenVal = constrain(greenVal, 127, 255);
  blueVal = constrain(blueVal, 127, 255);

//sensor setup
  deskTemp = DHT.temperature;

//diagnostics 
  Serial.print("Counter:");
  Serial.print(counter);
  Serial.println("");
  Serial.print("btnClk:");
  Serial.print(btnClk);
  Serial.println("");
  Serial.print("clkCounter:");
  Serial.print(clkCounter);
  Serial.println("");
  Serial.print("ledCounter:");
  Serial.print(ledCounter);
  Serial.println("");
  Serial.print("ledAdjCounter:");
  Serial.print(ledAdjCounter);
  Serial.println("");
  Serial.print("redVal:");
  Serial.print(redVal);  
  Serial.println("");
  Serial.println("");

//menu controls
  if (right == HIGH && clkCounter == 0 && ledCounter > 0) {
    counter++;
    lcd.clear();
    delay(100);
  } else if (left == HIGH && clkCounter == 0 && ledCounter > 0) {
    counter--;
    lcd.clear();
    delay(100);
  }

  if (btnClk == 1) {
    lcd.clear();
    delay(100);
  } 
  
//home and temp transitions
  if (btnClk == 1 && counter == 1 && clkCounter != 1) {
    clkCounter = clkCounter + 1;
    delay(100);
  } else if (btnClk == 1 && counter == 1 && clkCounter == 1) {
    clkCounter = clkCounter - 1; 
    delay(100);
  }
  if (btnClk == 1 && counter == 2 && clkCounter != 2) {
    clkCounter = clkCounter + 2;
    delay(100);
  }
    else if (btnClk == 1 && counter == 2 && clkCounter == 2 && ledCounter == 4) {
    clkCounter = clkCounter - 2;
    ledCounter = ledCounter - 3;  
    delay(100);
  }

//led menu transitions
  if (counter == 2 && clkCounter == 2 && ledAdjCounter == 0 && left == HIGH) {
    ledCounter--;
    lcd.clear(); 
    delay(100);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 0 && right == HIGH) {
    ledCounter++;
    lcd.clear();
    delay(100);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 1 && left == HIGH) {
    redVal = redVal - 1;
    lcd.clear();
    delay(2);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 1 && right == HIGH) {
    redVal = redVal + 1;
    lcd.clear();
    delay(2);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 3 && left == HIGH) {
    greenVal = greenVal - 1;
    lcd.clear();
    delay(2);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 3 && right == HIGH) {
    greenVal = greenVal + 1;
    lcd.clear();
    delay(2);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 5 && left == HIGH) {
    blueVal = blueVal - 1; 
    delay(2);
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 5 && right == HIGH) {
    blueVal = blueVal + 1;
    delay(2);
  }



  
//home menu
if (clkCounter == 0) {
ledAdjCounter = 0;
homeMenu(counter);
}
//temp menu
if (clkCounter == 1) {
  tempMenu(deskTemp);
}
//led menu
if (clkCounter == 2 && ledAdjCounter == 0) {
  ledMenu(redVal, greenVal, blueVal, ledCounter);
  delay(100);
} else if (clkCounter == 2 && ledAdjCounter > 0) {
  ledAdjustMenu(redVal, greenVal, blueVal, ledAdjCounter); 
  delay(100);
}

if (clkCounter == 2 && ledCounter == 1 && btnClk == HIGH) {
  lcd.clear();
  ledAdjCounter++;
} else if (clkCounter == 2 && ledCounter == 2 && btnClk == HIGH) {
  lcd.clear();
  ledAdjCounter = ledAdjCounter + 3; 
} else if (clkCounter == 2 && ledCounter == 3 && btnClk == HIGH) {
  lcd.clear();
  ledAdjCounter = ledAdjCounter + 5;
}
  else if (ledAdjCounter == 2) {
  lcd.clear();
  ledAdjCounter = 0;
} else if (ledAdjCounter == 6) {
  lcd.clear();
  ledAdjCounter = 0;
} else if (ledAdjCounter == 10) {
  lcd.clear();
  ledAdjCounter = 0;
}
}
