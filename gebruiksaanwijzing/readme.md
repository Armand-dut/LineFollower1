# Gebruiksaanwijzing – Arduino Line Follower

## 1. Aansluiten en voorbereiden

1. Sluit de Arduino Nano, de motorsdriver en de lijnsensor aan volgens het schema.
2. Upload `Linefollower_aangepast.ino` naar de Arduino Nano.
3. Zet de robot op een veilige plaats, bij voorkeur met de aangedreven wielen vrij van de grond tijdens de eerste motortest.
4. Open de Serial Monitor in de Arduino IDE.
5. Stel de baudrate in op **9600** en kies als regeleinde **Newline**.

**Let op:** de Bluetoothmodule gebruikt D0 en D1. Deze pinnen worden ook gebruikt voor de USB-seriële verbinding met de computer. Koppel de Bluetoothverbinding daarom los wanneer je via USB programmeert of de Serial Monitor gebruikt.

## 2. LED-indicatie

De ingebouwde LED op D13 geeft de toestand van het programma aan:

| LED | Betekenis |
|---|---|
| 3 korte flitsen | Arduino is opgestart |
| Knippert voortdurend | Line follower is actief |
| Uit | Robot staat stil |

## 3. Sensoren kalibreren

Kalibreer de sensoren bij voorkeur voor ieder gebruik. De meetwaarden kunnen veranderen door de ondergrond, de afstand tot de vloer en het omgevingslicht.

**Witte ondergrond:**

1. Plaats de volledige sensorbalk boven een witte ondergrond.
2. Stuur het commando:

   `calibrate white`

**Zwarte lijn/ondergrond:**

1. Plaats de volledige sensorbalk boven een zwarte ondergrond.
2. Stuur het commando:

   `calibrate black`

De waarden worden opgeslagen in het EEPROM-geheugen en blijven dus bewaard wanneer de Arduino wordt uitgeschakeld.

## 4. De robot starten en stoppen

| Commando | Werking |
|---|---|
| `run on` | Start de line follower |
| `run off` | Stopt de line follower |
| `debug` | Toont de ingestelde waarden en meetinformatie |

Zet de robot eerst op de lijn en controleer of de sensoren de lijn correct herkennen. Gebruik daarna `run on`.

## 5. Instellingen aanpassen

Je kunt de regelparameters aanpassen met het commando:

`set parameter waarde`

Voorbeelden:

| Commando | Betekenis |
|---|---|
| `set kp 1.5` | Past de proportionele regeling aan |
| `set ki 0.1` | Past de integrale regeling aan |
| `set kd 0.5` | Past de afgeleide regeling aan |
| `set power 100` | Past het basisvermogen van de motoren aan |
| `set diff 0.2` | Past het verschil tussen de motorvermogens aan |
| `set cycle 400` | Past de rekencyclus aan in microseconden |

De ingestelde waarden worden opgeslagen in EEPROM.

**Belangrijk:** verander de PID-waarden niet allemaal tegelijk. Pas telkens één waarde aan en test het resultaat.

## 6. Waarden controleren

Stuur:

`debug`

De Arduino toont onder andere:
- De ingestelde cyclustijd.
- De maximale rekentijd.
- De gekalibreerde sensorwaarden.
- De huidige positie van de lijn.
- De toestand van de `run`-variabele.
- De ingestelde Kp-, Ki-, Kd-, power- en diff-waarden.

## 7. Aanbevolen gebruiksvolgorde

1. Schakel de robot in.
2. Controleer of de LED 3 keer knippert.
3. Kalibreer met `calibrate white`.
4. Kalibreer met `calibrate black`.
5. Controleer eventueel de waarden met `debug`.
6. Plaats de robot op de lijn.
7. Start met `run on`.
8. Stop indien nodig met `run off`.
9. Pas de PID-instellingen aan als de robot niet goed volgt.

## 8. Problemen oplossen

- **De LED knippert niet bij het opstarten:** controleer of de Arduino correct is geprogrammeerd en voeding krijgt.
- **De robot rijdt de verkeerde kant op:** controleer de motorbedrading en de draairichting van de motoren.
- **De robot herkent de lijn niet:** voer de kalibratie opnieuw uit en controleer de sensorbedrading.
- **De robot reageert instabiel:** controleer de kalibratie en pas de PID-waarden stapsgewijs aan.
- **De Serial Monitor ontvangt geen commando's:** controleer de baudrate van 9600 en de instelling Newline.

**Veiligheid:** test de motoren eerst met de wielen vrij van de grond. Houd de robot vast of zorg dat hij voldoende vrije ruimte heeft wanneer je hem voor het eerst op de vloer laat rijden.

## 9. opladen / vervangen batterijen
Batterijen worden opgeladen met een lader die specifiek ontworpen is voor 18650 (Lithium) batterijen. Voor de batterijen kunnen worden ingestoken of verwijderd moet er gecontroleerd worden of de hoofdschekelaar van de pcb uitstaat (naar buitenste stand van de schakelaar)

## 10. draadloze communicatie
verbinding maken
We gebruiken een Hc-08, deze kan een signaal spanning aan van 3,2-6V op zijn TX & RX pinnen. En 3,2-6V op zijn VCC.

Een Hc-08 werkt op BLE (Bluetooth low energy), deze is dus compatible voor zowel android als iphone apparaten.

De applicatie die gebruikt werdt om de commandos te sturen is "serial bluetooth terminal", is beschikbaar op de google playstore en zou ook op de iphone app store beschikbaar moeten zijn.
