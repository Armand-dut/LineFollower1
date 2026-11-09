# Datasheets van de onderdelen

Hieronder staan de datasheets en componentinformatie die bij de line follower zijn gebruikt. De kolom **Belangrijk voor het project** vat samen waar je bij ontwerp, aansluiting of gebruik op moet letten.

| Onderdeel | Documentatie | Belangrijk voor het project |
|---|---|---|
| Arduino Nano | [Arduino Nano — datasheet (PDF)](A000005-datasheet.pdf) | De microcontroller leest de lijnsensoren uit en stuurt de motoren aan. Controleer de voedings- en logicaspanningen bij het aansluiten van andere modules. |
| 18650 Li-ion-batterij | [18650-cel, 2500 mAh — datasheet (PDF)](ASR00050_18650_2500mAh-3078640.pdf) | Voedingsbron van de robot. Let op de celspanning, laadvereisten en veilige omgang met Li-ion-cellen. |
| N20 DC-motor | [GA12-N20-motor — datasheet (PDF)](GA12-N20.pdf) | Aandrijving van de robot. De motor wordt via de motor driver aangestuurd; controleer de nominale spanning en stroom voor de gekozen motor. |
| HC-08 Bluetooth-module | [HC-08 Bluetooth-module — Engelstalige datasheet (PDF)](HC-08A%20version%20english%20datasheet.pdf) | Draadloze communicatie met de robot. Let op de voedingsspanning en de UART-signaalniveaus voordat je de module op de Arduino aansluit. |
| DRV8833 motor driver | [DRV8833 — datasheet (PDF)](drv8833.pdf) | Stuurt de twee DC-motoren aan vanuit de Arduino. Controleer de voedings- en stroomlimieten en sluit de motormassa en Arduino-massa op elkaar aan. |
| 8-kanaals IR-lijnsensor | [8x IR Line Tracking Module (HY-S301) — specificaties en aansluitingen](8x-ir-line-tracking-module.md) | Leest de reflectie van de ondergrond op acht posities, zodat de robot de lijn kan volgen. De documentatie beschrijft de signalen, voedingsspanning en belangrijke aandachtspunten voor aansluiten. |

De links verwijzen naar de bestanden in deze map. De beschikbare documenten geven niet voor elk onderdeel alle gegevens; controleer de datasheet zelf bij het bepalen van exacte spannings- en stroomlimieten.
