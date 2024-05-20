#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11
#define sensorPin 2

// RGB LED pins
int redpin = 9;
int bluepin = 10;
int greenpin = 8;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  displayTempAndHumidity(temperature, humidity);
  delay(1000);

  int lightValue = analogRead(sensorPin);
  setLEDColor(lightValue);
  //displayLightning(lightValue);
  //delay(5000);
}

void displayLightning(int value) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(value);
  lcd.setCursor(0, 1);
  if (value <= 100) {
    lcd.print("Tres lumineux");
  } else if (value > 100 && value <= 200) {
    lcd.print("Lumineux");
  } else if (value > 200 && value <= 300) {
    lcd.print("Peu lumineux");
    digitalWrite(bluepin, HIGH);
  } else {
    lcd.print("Pas lumineux");
  }
  setLEDColor(value);
}

void setLEDColor(int value) {
  if (value <= 50) {
    setColor(HIGH, LOW, LOW);
  } else if (value > 50 && value <= 150) {
    setColor(LOW, HIGH, LOW);
    } else if (value > 150 && value <= 250) {
    setColor(LOW, LOW, HIGH);
  } else {
    setColor(HIGH, LOW, HIGH);
  }
}

void setColor(bool red, bool green, bool blue) {
  digitalWrite(redpin, red);
  digitalWrite(greenpin, green);
  digitalWrite(bluepin, blue);
}

void displayTempAndHumidity(float temperature, float humidity) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
}
