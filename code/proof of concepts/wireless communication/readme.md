# Bluetooth (HC-08) – proof of concept

## Benodigdheden

- Arduino Nano
- HC-08 Bluetooth Low Energy-module (BLE)
- Twee leds, elk met een stroombegrenzende weerstand (bijvoorbeeld 220–330 Ω)
- Weerstanden van 1 kΩ en 2 kΩ voor de spanningsdeler tussen de Arduino en de HC-08
- Een smartphone met een BLE-UART- of seriële-terminalapp

## Aansluiten

Gebruik SoftwareSerial, zodat de USB-seriële pinnen D0 en D1 van de Nano vrij blijven:

| Arduino Nano | Aansluiten op |
| --- | --- |
| D10 (SoftwareSerial RX/ontvangen) | HC-08 TXD |
| D11 (SoftwareSerial TX/verzenden) | HC-08 RXD via de spanningsdeler van 1 kΩ en 2 kΩ hieronder |
| 3V3 | HC-08 VCC |
| GND | HC-08 GND en de onderkant van de spanningsdeler |
| D9 | Anode van led 1; sluit de kathode via een weerstand aan op GND |
| D6 (PWM) | Anode van led 2; sluit de kathode via een weerstand aan op GND |

De spanningsdeler verlaagt het 5V-zendsignaal van de Nano: D11 → 1 kΩ → knooppunt → HC-08 RXD. Sluit vanaf het knooppunt ook een weerstand van 2 kΩ aan op GND. Verbind alle aardpunten met elkaar. Voed de HC-08 met 3,3 V, zoals bij de gecontroleerde opstelling.

<img width="1169" height="827" alt="Schematic_LineFollower1_2026-11-09" src="https://github.com/user-attachments/assets/e06b03d4-7a90-4606-b6f2-92cd840ec65a" />


Het SVG-bestand hierboven is het aansluitschema voor deze sketch. Het oudere exportbestand `SCH_LineFollower1_2026-10-23 (1).json` is een verouderd projectschema en toont deze Bluetooth- en led-aansluitingen niet. Gebruik dat bestand daarom niet om deze proof of concept aan te sluiten.

## Commando's en duplexcommunicatie testen

Stel de UART-baudrate van de HC-08 in op 9600. Maak verbinding met een BLE-UART-app en verstuur commando's die eindigen op een nieuwe regel:

- `ON` — zet led 1 aan.
- `OFF` — zet led 1 uit.
- `PWM 128` — stel de helderheid van led 2 in op een waarde van 0 tot en met 255.
- `STATUS` — vraag de huidige ledstatus op.

De Arduino stuurt op elk commando een antwoord terug via Bluetooth. Onbekende of ongeldige commando's krijgen ook een foutmelding. Zo is communicatie in beide richtingen zichtbaar. De sketch toont de antwoorden ook in de USB-seriële monitor op 9600 baud.
