#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal_I2C.h>
#include <dht.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
dht DHT;

const byte ROWS = 1; 
const byte COLS = 4; 

char hexaKeys[ROWS] [COLS] = {
  {'E', 'R', 'L'}
};

byte rowPins[ROWS] = {8}; 
byte colPins[COLS] = {9, 10, 11};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

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
  pinMode(5, OUTPUT);
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
  int chk = DHT.read11(13);
  int pinStatus1 = digitalRead(1);
  int pinStatus2 = digitalRead(2); 
  int left = digitalRead(5);
  int right = digitalRead(4);
  int up = digitalRead(2);
  int down = digitalRead(1); 
  int btnClk = digitalRead(6); 
  int btnClk2 = digitalRead(6);
  static int i;
  static int j;
  static int deskTemp;
  static int counter = 1; 
  static int clkCounter = 0;
  static int ledCounter = 1;
  static int ledAdjCounter = 0;
  static int ledBuffer = 0;   
  static int redVal = 128;
  static int greenVal = 127;
  static int blueVal = 127;
  char customKey = customKeypad.getKey();
  
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
  Serial.println(j);

//menu controls
  if (customKey && clkCounter == 0 && ledCounter > 0) {
    if (customKey == 'R') {
    counter++;
    lcd.clear();
    delay(100);
    } else if (customKey == 'L') {
      counter--;
      lcd.clear();
      delay(100);
    } 
  }

  if (btnClk == 1 && i != 1) {
    lcd.clear();
    delay(100);
  } 
  
//home and temp transitions
  if (customKey && counter == 1 && clkCounter != 1) {
    if (customKey == 'E') {
    clkCounter = clkCounter + 1;
    lcd.clear();
    delay(100);
    }
  } else if (customKey && counter == 1 && clkCounter == 1) {
    if (customKey == 'E') {
    clkCounter = clkCounter - 1; 
    lcd.clear();
    delay(100);
    }
  }
  if (customKey && counter == 2 && clkCounter != 2) {
    if (customKey == 'E') {
    clkCounter = clkCounter + 2;
    lcd.clear();
    delay(100);
    }
  }
    else if (customKey && counter == 2 && clkCounter == 2 && ledCounter == 4) {
    if (customKey == 'E') {
    clkCounter = clkCounter - 2;
    ledCounter = ledCounter - 3;  
    lcd.clear();
    delay(100);
    }
  }

//led menu transitions
  if (counter == 2 && clkCounter == 2 && ledAdjCounter == 0 && customKey) {
    if(customKey == 'L') {
      ledCounter--;
      lcd.clear(); 
      delay(100);
    } else if (customKey == 'R') {
      ledCounter++;
      lcd.clear();
      delay(100);
    }
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 1 && customKey) {
      if (customKey == 'L') {
        redVal = redVal - 1;
        lcd.clear();
        delay(2);
      } else if (customKey == 'R') {
        redVal = redVal + 1;
        lcd.clear();
        delay(2);
      }
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 3 && customKey) {
      if (customKey == 'L') {
        greenVal = greenVal - 1;
        lcd.clear();
        delay(2);
      } else if (customKey == 'R') {
        greenVal = greenVal + 1;
        lcd.clear();
        delay(2);
      }
  } else if (counter == 2 && clkCounter == 2 && ledAdjCounter == 5 && customKey) {
      if (customKey == 'L') {
        blueVal = blueVal - 1; 
        delay(2);
      } else if (customKey == 'R') {
        blueVal = blueVal + 1;
        delay(2);
      }
  } 



  
//home menu
if (clkCounter == 0 && i == 0) {
ledAdjCounter = 0;
homeMenu(counter);
} else if (i == 1) {
    lcd.setCursor(0,0);
    lcd.print("Sanitation is");
    lcd.setCursor(0,1);
    lcd.print("ongoing...");
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

if (clkCounter == 2 && ledCounter == 1 && customKey && i == 0) {
  if (customKey == 'E') { 
    lcd.clear();
    ledAdjCounter++;
  }
} else if (clkCounter == 2 && ledCounter == 2 && customKey && i == 0) {
    if (customKey == 'E') {
      lcd.clear();
      ledAdjCounter = ledAdjCounter + 3;
    } 
} else if (clkCounter == 2 && ledCounter == 3 && customKey && i == 0) {
    if (customKey == 'E') {
      lcd.clear();
      ledAdjCounter = ledAdjCounter + 5;
    }
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

if (customKey && counter == 3 && customKey == 'E') {
  i = 1;
}

if (i == 1) {
  while(j < 10) {
    j = j + 1;
    digitalWrite(5, HIGH);
    delay(1000);
    break;
  }
if (j == 10) {
      digitalWrite(5, LOW);
      j = 0;
      i = 0;
      lcd.clear();
    }
}
}
