
const int knopPin = 2;
const int ledPin = 12;

volatile bool ledStatus = false;

void setup() {
  pinMode(knopPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  attachInterrupt(
    digitalPinToInterrupt(knopPin),
    knopInterrupt,
    RISING
  );
}

void loop() {
  noInterrupts();
  bool status = ledStatus;
  interrupts();

  digitalWrite(ledPin, status ? HIGH : LOW);
}

void knopInterrupt() {
  ledStatus = !ledStatus;
}

