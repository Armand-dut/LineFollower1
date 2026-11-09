/*
 ----------INSTRUCTIES HOE JE DEZE CODE GEBRUIKT EN WAARDES AANPAST------------
 -----------------------------------CB-----------------------------------------
 voor de waardes intestellen (diff, power, cycle,...) stuur je in de serial monitor => "set (naam) (value)"
 voor het instellen van de cyletime stuur in de serial monitor "set cyle 1000000", cycle time voor goede werking <500
 *
 voor calibratie sensor wit stuur in serial monitor "calibrate white" ----aangeraden om voor elk gebruik opnieuw tedoen, waardes kunnen veelverschillen afhankelijk van omgeving
 voor calibratie sensor zwart stuur in serial monitor "calibrate black" ----aangeraden om voor elk gebruik opnieuw tedoen, waardes kunnen veelverschillen afhankelijk van omgeving
 *
 om de opgeslagen waarden van het eeprom geheugen te controleren stuur je in de serial monitor "debug"
 diff <0.5 anders gaat er 1 van de motoren niet achteruit!!! (fysiek motor rechts, in de programmatie is dit motor links, ben te lui om dit aantepassen)
 *
 */

/*
  LINE FOLLOWER - ARDUINO NANO

  Commando's via Serial Monitor:
  set kp 1.5
  set ki 0.1
  set kd 0.5
  set power 100
  set diff 0.2
  set cycle 400

  calibrate white
  calibrate black
  debug
  run on
  run off

  LED D13:
  - 3 korte flitsen bij opstarten
  - Knippert tijdens het rijden
  - Uit wanneer de robot stilstaat
*/

#include "EEPROMAnything.h"

#define SerialPort Serial
#define Baudrate 9600

void onSet();
void onDebug();
void onCalibrate();
void onRun();
void onUnknownCommand(char* command);
void updateStatusLed();

char serialBuffer[80];
char *tokenContext = nullptr;

bool readSerialCommands() {
  static byte pos = 0;

  while (SerialPort.available()) {
    char c = (char)SerialPort.read();

    if (c == '\r') continue;

    if (c == '\n') {
      serialBuffer[pos] = '\0';
      pos = 0;

      char *command = strtok_r(serialBuffer, " ", &tokenContext);

      if (!command) return true;

      if (strcmp(command, "set") == 0) onSet();
      else if (strcmp(command, "debug") == 0) onDebug();
      else if (strcmp(command, "calibrate") == 0) onCalibrate();
      else if (strcmp(command, "run") == 0) onRun();
      else onUnknownCommand(command);

      return true;
    }

    if (pos < sizeof(serialBuffer) - 1) {
      serialBuffer[pos++] = c;
    } else {
      pos = 0;
    }
  }

  return false;
}

char* nextToken() {
  return strtok_r(nullptr, " ", &tokenContext);
}

bool run = false;
bool debug = false;

// Sensoren van links naar rechts
const int sensor[] = {
  A0, A1, A2, A3, A4, A5, A6, A7
};

unsigned long previous, calculationTime;

const int led = LED_BUILTIN;

long normalised[8];
float position;
int status = 0;
int index = 0;
float debugPosition;
float iTerm, lastErr;

// Motorpinnen volgens het schema
const int M1_IN1 = 5;
const int M1_IN2 = 6;
const int M2_IN3 = 10;
const int M2_IN4 = 11;

// EEPROM
struct param_t {
  unsigned long cycletime;
  int black[8];
  int white[8];
  float Kp;
  float Ki;
  float Kd;
  float diff;
  int power;
} params;


void setup() {

  ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
  ADCSRA |= (1 << ADPS2);

  SerialPort.begin(Baudrate);

  EEPROM_readAnything(0, params);

  SerialPort.println("ready");

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Drie korte flitsen bij het opstarten
  for (byte i = 0; i < 3; i++) {
    digitalWrite(led, HIGH);
    delay(150);
    digitalWrite(led, LOW);
    delay(150);
  }

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN3, OUTPUT);
  pinMode(M2_IN4, OUTPUT);
}


void loop() {

  updateStatusLed();

  readSerialCommands();

  unsigned long current = micros();

  if (current - previous >= params.cycletime) {

    previous = current;

    // Sensorwaarden normaliseren
    for (int i = 0; i < 8; i++) {
      long value = analogRead(sensor[i]);

      normalised[i] = map(
        value,
        params.black[i],
        params.white[i],
        0,
        1024
      );
    }

    // Sensor met laagste waarde zoeken
    index = 0;

    for (int i = 1; i < 8; i++) {
      if (normalised[i] < normalised[index]) {
        index = i;
      }
    }

    if (normalised[index] > 500) {
      run = false;
    }

    // Positie van de lijn berekenen
    if (index == 0) {
      position = -30;
    }
    else if (index == 7) {
      position = 30;
    }
    else {
      int sNul = normalised[index];
      int sMinEen = normalised[index - 1];
      int sPlusEen = normalised[index + 1];

      float b = sPlusEen - sMinEen;
      b = b / 2;

      float a = sPlusEen - b - sNul;

      position = -b / (2 * a);
      position += index;
      position -= 3.5;
      position *= 15;
    }

    // PID-regeling
    if (run == 1) {

      debugPosition = position;

      float error = -position;

      float output = error * params.Kp;

      // I-regelaar
      iTerm += params.Ki * error;
      iTerm = constrain(iTerm, -510, 510);

      output += iTerm;

      // D-regelaar
      output += params.Kd * (error - lastErr);
      lastErr = error;

      output = constrain(output, -510, 510);

      int powerLeft = 0;
      int powerRight = 0;

      if (output >= 0) {

        powerLeft = constrain(
          params.power + params.diff * output,
          -255,
          255
        );

        powerRight = constrain(
          powerLeft - output,
          -255,
          255
        );

        powerLeft = powerRight + output;
      }
      else {

        powerRight = constrain(
          params.power - params.diff * output,
          -255,
          255
        );

        powerLeft = constrain(
          powerRight + output,
          -255,
          255
        );

        powerRight = powerLeft - output;
      }

      analogWrite(
        M1_IN1,
        powerLeft > 0 ? powerLeft : 0
      );

      analogWrite(
        M1_IN2,
        powerLeft < 0 ? -powerLeft : 0
      );

      analogWrite(
        M2_IN3,
        powerRight > 0 ? powerRight : 0
      );

      analogWrite(
        M2_IN4,
        powerRight < 0 ? -powerRight : 0
      );
    }

    // Motoren stoppen
    if (run == 0) {

      digitalWrite(led, LOW);

      analogWrite(M1_IN1, LOW);
      analogWrite(M1_IN2, LOW);
      analogWrite(M2_IN3, LOW);
      analogWrite(M2_IN4, LOW);
    }

    unsigned long difference = micros() - current;

    if (difference > calculationTime) {
      calculationTime = difference;
    }
  }
}


// Onbekend commando
void onUnknownCommand(char* command) {

  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");

  run = false;
}


// Instellingen aanpassen
void onSet() {

  char* param = nextToken();
  char* value = nextToken();

  if (param == nullptr || value == nullptr) {
    SerialPort.println(
      "Gebruik: set <cycle|ki|kd|power|kp|diff> <waarde>"
    );
    return;
  }

  if (strcmp(param, "cycle") == 0) {

    long newCycleTime = atol(value);

    if (params.cycletime > 0 && newCycleTime > 0) {

      float ratio =
        ((float)newCycleTime) / ((float)params.cycletime);

      params.Ki *= ratio;
      params.Kd /= ratio;
    }

    params.cycletime = newCycleTime;
  }

  else if (strcmp(param, "ki") == 0) {

    float cycleTimeInSec =
      ((float)params.cycletime) / 1000000;

    params.Ki = atof(value) * cycleTimeInSec;
  }

  else if (strcmp(param, "kd") == 0) {

    float cycleTimeInSec =
      ((float)params.cycletime) / 1000000;

    params.Kd = atof(value) / cycleTimeInSec;
  }

  else if (strcmp(param, "power") == 0) {
    params.power = atol(value);
  }

  else if (strcmp(param, "kp") == 0) {
    params.Kp = atof(value);
  }

  else if (strcmp(param, "diff") == 0) {
    params.diff = atof(value);
  }

  else {
    SerialPort.println("Onbekende parameter");
    return;
  }

  EEPROM_writeAnything(0, params);

  SerialPort.println("Instelling opgeslagen");
}


// Debuginformatie
void onDebug() {

  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycletime);

  SerialPort.print("calculation time: ");
  SerialPort.println(calculationTime);

  calculationTime = 0;

  SerialPort.print("black: ");

  for (int i = 0; i < 8; i++) {
    SerialPort.print(params.black[i]);
    SerialPort.print(" ");
  }

  SerialPort.println();

  SerialPort.print("white: ");

  for (int i = 0; i < 8; i++) {
    SerialPort.print(params.white[i]);
    SerialPort.print(" ");
  }

  SerialPort.println();

  SerialPort.print("position: ");
  SerialPort.println(position);

  SerialPort.print("run: ");
  SerialPort.println(run);

  SerialPort.print("Kp: ");
  SerialPort.println(params.Kp);

  SerialPort.print("power: ");
  SerialPort.println(params.power);

  SerialPort.print("diff: ");
  SerialPort.println(params.diff);

  float cycleTimeInSec =
    ((float)params.cycletime) / 1000000;

  if (cycleTimeInSec > 0) {

    float ki = params.Ki / cycleTimeInSec;
    float kd = params.Kd * cycleTimeInSec;

    SerialPort.print("Ki: ");
    SerialPort.println(ki);

    SerialPort.print("Kd: ");
    SerialPort.println(kd);
  }
}


// Sensoren kalibreren
void onCalibrate() {

  char* param = nextToken();

  if (param == nullptr) {
    SerialPort.println("Gebruik: calibrate <black|white>");
    return;
  }

  digitalWrite(led, HIGH);

  if (strcmp(param, "black") == 0) {

    SerialPort.print("start calibrating black... ");

    for (int i = 0; i < 8; i++) {
      params.black[i] = analogRead(sensor[i]);
    }

    SerialPort.println("done");
  }

  else if (strcmp(param, "white") == 0) {

    SerialPort.print("start calibrating white... ");

    for (int i = 0; i < 8; i++) {
      params.white[i] = analogRead(sensor[i]);
    }

    SerialPort.println("done");
  }

  else {
    SerialPort.println("Gebruik black of white");
  }

  EEPROM_writeAnything(0, params);
}


// LED knippert tijdens het rijden
void updateStatusLed() {

  static unsigned long lastBlink = 0;
  static bool ledState = false;

  unsigned long now = millis();

  if (run) {

    if (now - lastBlink >= 250) {

      lastBlink = now;
      ledState = !ledState;

      digitalWrite(
        led,
        ledState ? HIGH : LOW
      );
    }
  }

  else {

    ledState = false;

    digitalWrite(led, LOW);

    lastBlink = now;
  }
}


// Robot starten en stoppen
void onRun() {

  char* parameter = nextToken();

  if (parameter == nullptr) {
    SerialPort.println("Gebruik: run <on|off>");
    return;
  }

  if (strcmp(parameter, "on") == 0) {

    iTerm = 0;
    run = true;

    digitalWrite(led, HIGH);
  }

  else if (strcmp(parameter, "off") == 0) {

    run = false;

    digitalWrite(led, LOW);
  }

  else {
    SerialPort.println("Gebruik: run <on|off>");
  }
}
