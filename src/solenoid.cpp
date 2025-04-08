#include "Solenoid.h"

Solenoid::Solenoid(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _isActive = false;
}

void Solenoid::activate()
{
    digitalWrite(_pin, HIGH);
    _isActive = true; // Set the state to active
}

void Solenoid::deactivate()
{
    digitalWrite(_pin, LOW);
    _isActive = false; // Set the state to inactive
}