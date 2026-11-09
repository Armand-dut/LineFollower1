#include <SoftwareSerial.h>

// Volgorde van SoftwareSerial: Arduino RX (ontvangen), Arduino TX (verzenden).
// Verbind HC-08 TXD met D10 en D11 via de spanningsdeler met HC-08 RXD.
SoftwareSerial BTserial(10, 11);

const byte led1Pin = 9;  // Led 1: aan/uit
const byte led2Pin = 6;  // Led 2: helderheid via PWM
int led2Value = 128;
bool led1On = false;

void reply(const String &message) {
  BTserial.println(message);
  Serial.println(message);
}

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  analogWrite(led2Pin, led2Value);

  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("HC-08-ledregeling gereed.");
}

void loop() {
  if (!BTserial.available()) {
    return;
  }

  String command = BTserial.readStringUntil('\n');
  command.trim();

  if (command.equalsIgnoreCase("ON")) {
    led1On = true;
    digitalWrite(led1Pin, HIGH);
    reply("OK: led 1 AAN");
  } else if (command.equalsIgnoreCase("OFF")) {
    led1On = false;
    digitalWrite(led1Pin, LOW);
    reply("OK: led 1 UIT");
  } else if (command.startsWith("PWM ")) {
    String valueText = command.substring(4);
    valueText.trim();

    bool valid = valueText.length() > 0;
    for (unsigned int i = 0; i < valueText.length(); ++i) {
      if (!isDigit(valueText[i])) {
        valid = false;
        break;
      }
    }

    int value = valid ? valueText.toInt() : -1;
    if (valid && value >= 0 && value <= 255) {
      led2Value = value;
      analogWrite(led2Pin, led2Value);
      reply("OK: PWM led 2 = " + String(led2Value));
    } else {
      reply("FOUT: gebruik PWM 0..255");
    }
  } else if (command.equalsIgnoreCase("STATUS")) {
    reply(String("Led 1=") + (led1On ? "AAN" : "UIT") +
          ", PWM led 2=" + String(led2Value));
  } else {
    reply("FOUT: gebruik ON, OFF, PWM 0..255 of STATUS");
  }
}
