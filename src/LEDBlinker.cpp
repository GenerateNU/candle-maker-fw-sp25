#include "LEDBlinker.h"

LEDBlinker::LEDBlinker(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _interval = 1000; // Default interval
  _previousMillis = 0;
  _ledState = LOW;
  int pinA = 11;
  int pinB = 12;
}

void LEDBlinker::blink(unsigned long interval) {
  _interval = interval;
  unsigned long currentTimeMillis = millis();

  if (currentTimeMillis - _previousMillis >= _interval) {
    _previousMillis = currentTimeMillis;
    _ledState = !_ledState;
    digitalWrite(_pin, _ledState);
  }
}