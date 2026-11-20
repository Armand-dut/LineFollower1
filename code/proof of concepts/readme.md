# Proof of Concepts

Een proof of concept is een combinatie van minimale hard- en software om eenvoudig aan te tonen dat iets werkt.  
Proof of concepts kunnen enerzijds als eerste poging dienen om een bepaald onderdeel van het project werkend te krijgen. Anderzijds kunnen ze tijdens het debuggen van het finale project dienen als test om eventuele hardware problemen te elimineren bij onduidelijke problemen.
<br />  
<br />
Een proof of concept bestaat uit
* een elektronisch schema (indien van toepassing)
* minimale code om de voorop gestelde zaken te demonstreren
* minimale uitleg / aandachtspunten
<br />
De elektronische schakelingen van de proof of concepts komen bij voorkeur overeen met deze van de uiteindelijke linefollower, zodat de code zonder aanpassingen op het finale project kan draaien.

## Verschillen t.o.v. de Proofs of Concept (LED's)

De externe LED's uit de Proofs of Concept (op D6, D9 en D12) en een aparte power-on-LED zijn weggelaten in het volledige schema om de volgende redenen:

* **Interne LED's benutten:** De Arduino Nano heeft al een ingebouwde status-LED (`LED_BUILTIN` op pin D13) en een vaste `ON`-LED voor de voeding. Externe LED's voor status en spanning zijn daarom niet nodig.
* **Eenvoudiger circuit:** Minder losse LED's en voorschakelweerstanden houden het schema overzichtelijker en verkleinen de kans op bedradingsfouten.
* **Pinbesparing:** De losse LED's op D6, D9 en D12 waren enkel bedoeld om deelfuncties te testen; in het uiteindelijke ontwerp blijven deze I/O-pinnen vrij.
