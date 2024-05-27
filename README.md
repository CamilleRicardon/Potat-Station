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
    HX710B Pressure sensor

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

    PRESSURE Sensor:
        CLK 24
        OUT 22
        VCC +5V
        GND GND

CODE
      #include <LiquidCrystal.h>
      #include "DHT.h"

      #define DHTPIN 6
      #define DHTTYPE DHT11
      #define sensorPin 2

      //Pressure sensor
      const int hx710bDataPin = 22;
      const int hx710bClockPin = 24;

      // RGB LED pins
      int redpin = 9;
      int bluepin = 10;
      int greenpin = 8;

      DHT dht(DHTPIN, DHTTYPE);
      LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

      void setup() {
        Serial.begin(9600);
        lcd.begin(16, 2);
        dht.begin();
        pinMode(redpin, OUTPUT);
        pinMode(bluepin, OUTPUT);
        pinMode(greenpin, OUTPUT);

        pinMode(hx710bClockPin, OUTPUT);
        pinMode(hx710bDataPin, INPUT);
        digitalWrite(hx710bClockPin, LOW);
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
        delay(3000);

        long rawPressure = readHX710B();
        Serial.print("Pressure (raw): ");
        Serial.println(rawPressure);

        float pressure = convertToPressureInHpa(rawPressure);
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");

        displayPressure(pressure);
        delay(3000);
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

      void displayPressure(float pressure) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pressure: ");
        lcd.print(pressure);
        lcd.setCursor(0, 1);
        lcd.print(" hPa");
      }

      long readHX710B() {
        long count = 0;
        while (digitalRead(hx710bDataPin));

        for (int i = 0; i < 24; i++) {
          digitalWrite(hx710bClockPin, HIGH);
          delayMicroseconds(1);
          count = count << 1;
          digitalWrite(hx710bClockPin, LOW);
          if (digitalRead(hx710bDataPin)) {
            count++;
          }
          delayMicroseconds(1);
        }

        digitalWrite(hx710bClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(hx710bClockPin, LOW);
        delayMicroseconds(1);
        digitalWrite(hx710bClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(hx710bClockPin, LOW);

        count ^= 0x800000;

        return count;
      }

      float convertToPressureInHpa(long rawValue) {
        float pressureFactor = 1.0 / 10000.0;
        return rawValue * pressureFactor;
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

    displayPressure(float pressure) function:
        Displays the pressure in hPa on the LCD screen.

    longRead() function:
        Get the raw value of pressure sensor in Pa.

    convertToPressureInHpa(long rawValue) function:
        Convert the raw value in Pa in hPa.
