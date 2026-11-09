#include <SoftwareSerial.h>

// SoftwareSerial constructor order: Arduino RX, Arduino TX.
// Connect HC-08 TXD to D10 and D11 to HC-08 RXD through the level divider.
SoftwareSerial BTserial(10, 11);

const byte led1Pin = 9;  // LED 1: on/off
const byte led2Pin = 6;  // LED 2: PWM brightness
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
  Serial.println("HC-08 dual LED control ready.");
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
    reply("OK: LED1 ON");
  } else if (command.equalsIgnoreCase("OFF")) {
    led1On = false;
    digitalWrite(led1Pin, LOW);
    reply("OK: LED1 OFF");
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
      reply("OK: LED2 PWM " + String(led2Value));
    } else {
      reply("ERROR: use PWM 0..255");
    }
  } else if (command.equalsIgnoreCase("STATUS")) {
    reply(String("LED1=") + (led1On ? "ON" : "OFF") +
          ", LED2_PWM=" + String(led2Value));
  } else {
    reply("ERROR: use ON, OFF, PWM 0..255, or STATUS");
  }
}
