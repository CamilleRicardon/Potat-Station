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
