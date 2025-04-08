// SOLENOID.h

#ifndef SOLENOID_h
#define SOLENOID_h

#include "Arduino.h"

class Solenoid {
  public:
    Solenoid(int pin);
    void activate();
    void deactivate();

  private:
    int _pin;
    bool _isActive;
};

#endif
