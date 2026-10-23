const int IN1 = 5;
const int IN2 = 6;
const int IN3 = 9;
const int IN4 = 10;
const int FAULT = 4;

int snelheidA = 0;
int snelheidB = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // FAULT heeft een externe pull-up van 10 kΩ
  pinMode(FAULT, INPUT);

  Serial.begin(9600);
  stopMotoren();

  Serial.println("DRV8833 motor test");
  Serial.println("Gebruik: A 150, B -100, A 0");
}

void loop() {
  if (Serial.available() > 0) {
    char motor = Serial.read();

    if (motor == 'A' || motor == 'a' ||
        motor == 'B' || motor == 'b') {

      int snelheid = Serial.parseInt();
      snelheid = constrain(snelheid, -255, 255);

      if (motor == 'A' || motor == 'a') {
        snelheidA = snelheid;
        stelMotorIn(IN1, IN2, snelheidA);
        Serial.print("Motor A: ");
        Serial.println(snelheidA);
      } else {
        snelheidB = snelheid;
        stelMotorIn(IN3, IN4, snelheidB);
        Serial.print("Motor B: ");
        Serial.println(snelheidB);
      }
    }

    while (Serial.available() > 0) {
      Serial.read();
    }
  }

  if (digitalRead(FAULT) == LOW) {
    Serial.println("WAARSCHUWING: DRV8833 FAULT!");
    delay(500);
  }
}

void stelMotorIn(int pin1, int pin2, int snelheid) {
  if (snelheid > 0) {
    analogWrite(pin1, snelheid);
    analogWrite(pin2, 0);
  } else if (snelheid < 0) {
    analogWrite(pin1, 0);
    analogWrite(pin2, -snelheid);
  } else {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  }
}

void stopMotoren() {
  stelMotorIn(IN1, IN2, 0);
  stelMotorIn(IN3, IN4, 0);
}
