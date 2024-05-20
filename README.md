Arduino Code Documentation for Temperature, Humidity and Light Sensor with LCD and RGB LED Display

Description

This project uses a DHT11 sensor to measure temperature and humidity, a photo-resistance to measure ambient light, and displays the results on an LCD screen. In addition, an RGB LED changes color depending on the light intensity detected.

Necessary Equipment

    Arduino Uno
    Sensor DHT11
    Photo-resistance
    Various resistances
    16x2 LCD screen
    RGB LED
    Breadboard and connection wires

Connection Scheme

    DHT11 sensor:
        5V VDC pin
        GND GND Pin
        Pin DATA Digital Pin 6

    Photo-resistance:
        A pin connected to +5V
        The other pin connected to a 10kΩ resistor, and the analog pin A0
        The other end of the resistor connected to GND

    RGB LED:
        Common cathode (if RGB LED with common cathode) connected to GND
        Red anode connected to digital pin 9 via a resistor of 220Ω
        Green anode connected to digital pin 8 via a resistor of 220Ω
        Blue anode connected to digital pin 10 via a resistor of 220Ω

    LCD screen:
        VSS GND
        VDD +5V
        V0 Potentiometer for contrast adjustment
        RS Digital Pin 12
        RW GND
        E Digital Pin 11
        D4 Digital Pin 5
        D5 Digital Pin 4
        D6 Digital Pin 3
        D7 Digital Pin 2
        A +5V (backlight)
        K GND (backlight)

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

Explanation of the Code

    Libraries:
        #include <LiquidCrystal. h>: to control the LCD screen.
        #include "DHT. h": to use the DHT11 sensor.

    Definition of Pins:
        #define DHTPIN 6: DHT11 sensor pin.
        #define DHTTYPE DHT11: DHT sensor type.
        #define sensorPin A0: Analog pin for photo-resistance.

    RGB LED pins:
        int redpin = 9;
        int bluepin = 10;
        int greenpin = 8;

    Initialization:
        dht dht(dhtpin, dhttype);
        LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

    Setup() function:
        Initializes the LCD and DHT sensor.
        Sets the RGB LED pins as outputs.

    Loop() function:
        Reads temperature and humidity.
        Displays the values on the LCD screen.
        Reads the light value and changes the RGB LED color accordingly.

    displayLightning(int value) function:
        Displays the light level and a description on the LCD screen.

    setLEDColor(int value) function:
        Changes the color of the RGB LED according to the light value read.

    setColor(bool red, bool green, bool blue) function:
        Changes the state of the RGB LED pins.

    displayTempAndHumidity(float temperature, float humidity) function:
        Displays temperature and humidity on the LCD.
