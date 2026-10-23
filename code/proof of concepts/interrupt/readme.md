## Start/stop-drukknop met hardware-interrupt

## Hardware
- Arduino Nano
- Drukknop S2 aangesloten op pin D2 en VCC
- Pull-downweerstand R4 van 10 kΩ tussen D2 en GND
- LED op pin D12 met een serieweerstand R5 van 450 Ω

## Software
De Arduino gebruikt een hardware-interrupt met `RISING`. Wanneer de drukknop wordt ingedrukt, verandert het signaal op pin D2 van LOW naar HIGH. De interruptfunctie wisselt vervolgens de status van de LED.

## Werking
Bij de eerste druk gaat de LED aan. Bij de volgende druk gaat de LED uit. Zo wordt de start/stop-functionaliteit met een hardware-interrupt aangetoond.

## Schema
<img width="1169" height="827" alt="Schematic_LineFollower1_2026-10-23 (2)" src="https://github.com/user-attachments/assets/4d49db3f-2c2d-4912-9292-78df4ff9573c" />

