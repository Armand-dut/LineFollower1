## Minimale hard- en software
Arduino Uno, HC-05 Bluetoothmodule, twee leds en een smartphone met een Bluetooth-terminalapp.

## Configuratie
HC-05 op pinnen 10 en 11. LED 1 op pin 9 en LED 2 op PWM-pin 6. Baudrate: 9600.

## Opmerkingen
`ON` en `OFF` bedienen LED 1. `PWM 128` regelt de helderheid van LED 2. Voor duplexcommunicatie stuurt de Arduino ook berichten terug via Bluetooth.

## Gebruiksaanwijzing
Upload de code, verbind de smartphone met de HC-05 en verstuur commando's via de Bluetooth-terminalapp. Controleer de werking van de leds en de ontvangen antwoorden.

## Schema
<img width="1169" height="827" alt="Bluetooth" src="https://github.com/user-attachments/assets/617b1de0-2707-4c45-abb7-3fe086f87bf4" />
