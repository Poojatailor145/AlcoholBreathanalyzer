#include <Wire.h>             
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledPin = 7;
int sensorPin = A0;
int value;
int adjustedValue;

void setup() {
  Serial.begin(9600);
  lcd.init();                  
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  value = analogRead(sensorPin);
  adjustedValue = value - 50;  // Adjust the sensor value
  lcd.clear();
  lcd.setCursor(0, 0);

  // Choose the message based on the sensor value.
  if (adjustedValue < 100) {
    lcd.print("Alc: <5%, <100");
  } else if (adjustedValue <= 170) {
    lcd.print("Alc: 5-10%, >100");
  } else if (adjustedValue <= 250) {
    lcd.print("Alc: 10-20%, >170");
  } else if (adjustedValue <= 350) {
    lcd.print("Alc: 21-35%, >250");
  } else {
    lcd.print("Alc: >35%, >350");
    digitalWrite(ledPin, HIGH); // High alcohol level alert
  }

  // Turn off the LED if the alcohol level is not the highest.
  if (adjustedValue <= 350) {
    digitalWrite(ledPin, LOW);
  }

  // Set the cursor to the second line for additional messages.
  lcd.setCursor(0, 1);
  if (adjustedValue > 350) {
    lcd.print("Alert: High Alc!");
  } else {
    lcd.print("Level: Normal");
  }
  
  // Print the raw value to the Serial Monitor for debugging.
  Serial.print("Sensor Value: ");
  Serial.print(adjustedValue);
  if (adjustedValue > 350) {
    Serial.println(", High Alc!");
  } else {
    Serial.println(", Normal Alc");
  }
  
  delay(500);
}