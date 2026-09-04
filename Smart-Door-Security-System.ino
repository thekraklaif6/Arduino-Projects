#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


const int GREEN_LED = A0;
const int RED_LED   = A1;
const int BUZZER    = A2; 

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String CORRECT_PASS = "2580";
String inputPassword = "";

int failedAttempts = 0;
const int MAX_ATTEMPTS = 2;
bool isLocked = false;


void playSuccessSound() {
  digitalWrite(BUZZER, HIGH); delay(100);
  digitalWrite(BUZZER, LOW);  delay(80);
  digitalWrite(BUZZER, HIGH); delay(200);
  digitalWrite(BUZZER, LOW);
}


void playErrorSound() {
  digitalWrite(BUZZER, HIGH); delay(600);
  digitalWrite(BUZZER, LOW);
}


void playKeySound() {
  digitalWrite(BUZZER, HIGH); delay(20);
  digitalWrite(BUZZER, LOW);
}

void showHomeScreen() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  lcd.print("or Scan Card...");
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();
  showHomeScreen();
}

void loop() {
  
  if (isLocked) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Locked!");
    lcd.setCursor(0, 1);
    lcd.print("Too Many Tries");
    
  
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER, HIGH); delay(150);
      digitalWrite(BUZZER, LOW);  delay(150);
    }
    
    delay(30000); 
    
    failedAttempts = 0;
    isLocked = false;
    showHomeScreen();
    return;
  }

  char key = keypad.getKey();
  
  if (key) {
    playKeySound(); 

    if (inputPassword.length() == 0) {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Key: ");
    }
    
    inputPassword += key;
    lcd.print("*");

    if (inputPassword.length() == 4) {
      delay(300);
      lcd.clear();

      if (inputPassword == CORRECT_PASS) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);

        lcd.setCursor(0, 0);
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Door Unlocked");
        
        playSuccessSound();
        
        failedAttempts = 0;
        delay(2000);
        inputPassword = "";
        showHomeScreen();
      } 
      else {
        failedAttempts++;
        
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

        if (failedAttempts >= MAX_ATTEMPTS) {
          isLocked = true;
        } else {
          lcd.setCursor(0, 0);
          lcd.print("Access Denied!");
          lcd.setCursor(0, 1);
          lcd.print("Try Again (1/2)");
          
          playErrorSound();
          
          delay(2000);
          inputPassword = "";
          showHomeScreen();
        }
      }
    }
  }
}
