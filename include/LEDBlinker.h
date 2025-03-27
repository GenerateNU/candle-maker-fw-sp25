// LEDBlinker.h

#ifndef LEDBlinker_h
#define LEDBlinker_h

#include "Arduino.h"

class LEDBlinker {
  public:
    LEDBlinker(int pin);
    void blink(unsigned long interval);
    void turnOn();

  private:
    int _pin;
    unsigned long _interval;
    unsigned long _previousMillis;
    int _ledState;
};

#endif
