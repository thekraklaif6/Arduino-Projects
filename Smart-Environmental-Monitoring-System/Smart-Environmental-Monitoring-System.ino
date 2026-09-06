#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>


#define DHTPIN 2          
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);


LiquidCrystal_I2C lcd(0x27, 16, 2); 


const int LDR_LEFT_PIN     = A0;
const int LDR_RIGHT_PIN    = A1;
const int WATER_SENSOR_PIN = A2;


const int BUZZER_PIN    = 3; 
const int GREEN_LED_PIN = 4; 
const int RED_LED_PIN   = 5; 
const int FAN_PIN       = 6; 


const float TEMP_THRESHOLD = 30.0;

void setup() {
  Serial.begin(9600);
  
  
  dht.begin();
  lcd.init();
  lcd.backlight();

  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  noTone(BUZZER_PIN);

 
  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  delay(1500);
  lcd.clear();
}

void loop() {
  
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  int ldrLeft = analogRead(LDR_LEFT_PIN);
  int ldrRight = analogRead(LDR_RIGHT_PIN);
  int avgLight = (ldrLeft + ldrRight) / 2;
  int lightPercent = map(avgLight, 0, 1023, 0, 100);

  
  int waterRaw = analogRead(WATER_SENSOR_PIN);
  int waterPercent = map(waterRaw, 0, 700, 0, 100);
  waterPercent = constrain(waterPercent, 0, 100);

  
  bool isHot = (tempC >= TEMP_THRESHOLD);
  if (isHot) {
    digitalWrite(FAN_PIN, HIGH); 
  } else {
    digitalWrite(FAN_PIN, LOW);  

 
  bool isDanger = (waterPercent < 15) || isHot;

  if (isDanger) {
    digitalWrite(GREEN_LED_PIN, LOW);  
    digitalWrite(RED_LED_PIN, HIGH);   
    tone(BUZZER_PIN, 1000);            
  } else {
    digitalWrite(RED_LED_PIN, LOW);     
    digitalWrite(GREEN_LED_PIN, HIGH); 
    noTone(BUZZER_PIN);                

  
  Serial.print("Temp: "); Serial.print(tempC); Serial.print("C | ");
  Serial.print("Hum: "); Serial.print(humidity); Serial.print("% | ");
  Serial.print("Light: "); Serial.print(lightPercent); Serial.print("% | ");
  Serial.print("Water: "); Serial.print(waterPercent); Serial.print("% | ");
  Serial.print("Fan: "); Serial.println(isHot ? "ON" : "OFF");

 
  if (isnan(humidity) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT Sensor Error");
  } else {
    
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print((int)tempC); lcd.print("C ");
    lcd.print("H:"); lcd.print((int)humidity); lcd.print("% ");
    lcd.print("L:"); lcd.print(lightPercent); lcd.print("%");

    
    lcd.setCursor(0, 1);
    lcd.print("W:"); lcd.print(waterPercent); lcd.print("% ");
    
    if (isHot) {
      lcd.print("FAN:ON ");
    } else {
      lcd.print("FAN:OFF");
    }
  }

  delay(500); 
}
