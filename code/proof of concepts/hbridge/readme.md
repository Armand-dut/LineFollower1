# H-Bridge proof of concept

## Doel
Aantonen dat twee DC-motoren onafhankelijk van elkaar kunnen draaien, met een regelbare snelheid en draairichting via een DRV8833 H-brug.

## Hardware
- Arduino Nano
- DRV8833 H-brugmotorsturing
- Twee DC-motoren
- Voeding voor de motoren
- 10 kΩ pull-upweerstand op de FAULT-uitgang naar VCC
- FAULT aangesloten op digitale pin D4

De motoren worden aangestuurd met vier PWM-pinnen:
- Motor A: D5 en D6
- Motor B: D9 en D10

## Software
De snelheid wordt ingesteld met PWM. Een positieve waarde laat de motor vooruit draaien, een negatieve waarde laat de motor achteruit draaien en nul stopt de motor.

Via de seriële monitor kunnen beide motoren afzonderlijk worden aangestuurd. De FAULT-uitgang wordt uitgelezen om een foutmelding van de motorsturing te detecteren.

## Testprocedure
1. Sluit de hardware aan volgens het elektrisch schema.
2. Upload de Arduino-code.
3. Open de seriële monitor op 9600 baud.
4. Stuur `A 150` om motor A te laten draaien.
5. Stuur `B -100` om motor B in de tegenovergestelde richting te laten draaien.
6. Verander de snelheden en controleer dat beide motoren onafhankelijk reageren.
7. Stuur `A 0` of `B 0` om de betreffende motor te stoppen.

## Resultaat
De proof of concept is geslaagd wanneer beide motoren afzonderlijk kunnen starten, stoppen, hun draairichting kunnen veranderen en verschillende snelheden kunnen aannemen. De FAULT-status wordt eveneens via de seriële monitor weergegeven.

## Schema
<img width="1169" height="827" alt="Schematic_LineFollower1_2026-10-23 (4)" src="https://github.com/user-attachments/assets/2fbe17f6-295b-4760-b12d-0aafceb4e3e8" />
