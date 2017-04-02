#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <EEPROM.h>

Adafruit_7segment matrix = Adafruit_7segment();
const int resetPin = 7;
const int resetDelay = 1000;
const int counterPin = 4;
const int counterDelay = 500;
const int eeAddress = 0;

/* set this line for # of hits between change */
const int multi = 3;

int count;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(resetPin, INPUT_PULLUP);
  pinMode(counterPin, INPUT_PULLUP);
  matrix.begin(0x70);
  
  Serial.print("Read float from EEPROM: ");
  EEPROM.get(eeAddress, count);
  if (count < 0) {
    count = 0;
  }
  Serial.println(count, DEC);
  printDecimal(count);
}

void loop() {
  int resetReading = digitalRead(resetPin);
  if (resetReading == LOW) {
    count = 0;
    stateChange(count);
    delay(resetDelay);
    Serial.println("reset button after delay");
  }

  int counterReading = digitalRead(counterPin);
  if (counterReading == LOW) {
    count++;
    stateChange(count / multi);
    delay(counterDelay);
    Serial.println("count button after delay");
  }
}

void stateChange(int count) {
  printDecimal(count);
  EEPROM.put(eeAddress, count);
  Serial.print("state change:  ");
  Serial.println(count, DEC);
}

void printDecimal(int val) {
  matrix.print(val, DEC);
  matrix.writeDisplay();
}
