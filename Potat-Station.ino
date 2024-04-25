#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11

//définition du capteur temp
DHT dht(DHTPIN, DHTTYPE);

// Définition des broches utilisées pour l'écran LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int LED = 24;
const int motionSensor = 7;
int sensorValue = 0;

void setup() {
  // Initialise l'écran LCD avec 16 colonnes et 2 lignes
  lcd.begin(16, 2);
  dht.begin();
  pinMode(LED, OUTPUT);
  pinMode(motionSensor, INPUT);
  
}

void loop() {
  // Lecture de la température et de l'humidité depuis le capteur
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  sensorValue = digitalRead(motionSensor);

  if (sensorValue == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MOTION: ");
  lcd.print(sensorValue);
  // Affichage des valeurs sur l'écran LCD
  // lcd.clear(); // Efface le contenu précédent de l'écran LCD
  // lcd.setCursor(0, 0); // Positionne le curseur en haut à gauche
  // lcd.print("Temp: "); // Affiche le texte "Temp: "
  // lcd.print(temperature); // Affiche la température
  // lcd.print(" C"); // Affiche l'unité de température

  // lcd.setCursor(0, 1); // Positionne le curseur en bas à gauche
  // lcd.print("Humidity: "); // Affiche le texte "Humidity: "
  // lcd.print(humidity); // Affiche l'humidité
  // lcd.print(" %"); // Affiche l'unité d'humidité
  
  // Attente de quelques secondes avant de lire à nouveau les données du capteur
  delay(1000);
}