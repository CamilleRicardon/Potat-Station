Documentation du Code Arduino pour Capteur de Température, Humidité et Lumière avec Affichage LCD et LED RGB

Description

Ce projet utilise un capteur DHT11 pour mesurer la température et l'humidité, un photo-résistance pour mesurer la lumière ambiante, et affiche les résultats sur un écran LCD. De plus, une LED RGB change de couleur en fonction de l'intensité lumineuse détectée.

Matériel Nécessaire

    Arduino Uno
    Capteur DHT11
    Photo-résistance
    Résistances diverses
    Écran LCD 16x2
    LED RGB
    Breadboard et fils de connexion

Schéma de Connexion

    Capteur DHT11:
        Pin VCC → 5V
        Pin GND → GND
        Pin DATA → Pin numérique 6

    Photo-résistance:
        Une broche connectée à +5V
        L'autre broche connectée à une résistance de 10kΩ, et à la pin analogique A0
        L'autre extrémité de la résistance connectée à GND

    LED RGB:
        Cathode commune (si LED RGB à cathode commune) connectée à GND
        Anode rouge connectée à la pin numérique 9 via une résistance de 220Ω
        Anode verte connectée à la pin numérique 8 via une résistance de 220Ω
        Anode bleue connectée à la pin numérique 10 via une résistance de 220Ω

    Écran LCD:
        VSS → GND
        VDD → +5V
        V0 → Potentiomètre pour réglage du contraste
        RS → Pin numérique 12
        RW → GND
        E → Pin numérique 11
        D4 → Pin numérique 5
        D5 → Pin numérique 4
        D6 → Pin numérique 3
        D7 → Pin numérique 2
        A → +5V (rétro-éclairage)
        K → GND (rétro-éclairage)

CODE

    #include <LiquidCrystal.h>
    #include "DHT.h"
    #define DHTPIN 6
    #define DHTTYPE DHT11
    #define sensorPin A0 // Pin pour la photo-résistance
    // Pins LED RGB
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
      delay(1000); // Courte pause pour la réactivité
      int lightValue = analogRead(sensorPin);
      setLEDColor(lightValue);
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
    digitalWrite(bluepin, HIGH); // Bleu
      } else {
    lcd.print("Pas lumineux");
      }
      setLEDColor(value); // Change la couleur de la LED en fonction de la lumière
    }
    void setLEDColor(int value) {
      if (value <= 50) {
    setColor(HIGH, LOW, LOW); // Rouge
      } else if (value > 50 && value <= 150) {
    setColor(LOW, HIGH, LOW); // Vert
      } else if (value > 150 && value <= 250) {
    setColor(LOW, LOW, HIGH); // Bleu
      } else {
    setColor(HIGH, LOW, HIGH); // Magenta
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

Explication du Code

    Bibliothèques:
        #include <LiquidCrystal.h> : pour contrôler l'écran LCD.
        #include "DHT.h" : pour utiliser le capteur DHT11.

    Définition des Pins:
        #define DHTPIN 6 : Pin du capteur DHT11.
        #define DHTTYPE DHT11 : Type de capteur DHT.
        #define sensorPin A0 : Pin analogique pour la photo-résistance.

    Pins LED RGB :
        int redpin = 9;
        int bluepin = 10;
        int greenpin = 8;

    Initialisation :
        DHT dht(DHTPIN, DHTTYPE);
        LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

    Fonction setup() :
        Initialise l'écran LCD et le capteur DHT.
        Définit les pins de la LED RGB comme sorties.

    Fonction loop() :
        Lit la température et l'humidité.
        Affiche les valeurs sur l'écran LCD.
        Lit la valeur de lumière et change la couleur de la LED RGB en conséquence.

    Fonction displayLightning(int value) :
        Affiche le niveau de lumière et une description sur l'écran LCD.

    Fonction setLEDColor(int value) :
        Change la couleur de la LED RGB en fonction de la valeur de lumière lue.

    Fonction setColor(bool red, bool green, bool blue) :
        Change l'état des pins de la LED RGB.

    Fonction displayTempAndHumidity(float temperature, float humidity) :
        Affiche la température et l'humidité sur l'écran LCD.
