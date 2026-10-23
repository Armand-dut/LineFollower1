# Sensoren proof of concept

## Doel
Aantonen dat minimaal zes sensoren onafhankelijk van elkaar kunnen worden uitgelezen. De HY-S301-sensor heeft acht analoge uitgangen die aangesloten zijn op A0 tot en met A7 van de Arduino Nano.

Er wordt geen calibratie, normalisatie of interpolatie toegepast. De ruwe waarden van de ADC worden rechtstreeks uitgelezen. Bij de Arduino Nano worden deze waarden weergegeven in het bereik van 0 tot 1023 (10-bit ADC).

## Hardware
- Arduino Nano
- HY-S301-lijnsensor met acht analoge uitgangen
- Sensoruitgangen aangesloten op A0 tot en met A7
- Stuurpin R1 aangesloten op digitale pin D7

## Software
De Arduino leest elke 200 ms de acht analoge ingangen afzonderlijk uit en toont de ruwe meetwaarden via de seriële monitor op 9600 baud.

De IR-stuurpin wordt tijdens de test HIGH gemaakt om de sensor in te schakelen.

## Testresultaat
In de seriële monitor worden acht afzonderlijke sensorwaarden weergegeven. Door de sensoren afzonderlijk te belichten of af te schermen, kan gecontroleerd worden of de meetwaarden onafhankelijk veranderen.

## Schema
<img width="1169" height="827" alt="Schematic_LineFollower1_2026-10-23 (3)" src="https://github.com/user-attachments/assets/54e32763-4b67-430d-b197-f79b7302a5e1" />
