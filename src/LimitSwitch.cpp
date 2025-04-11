//#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(uint8_t pin) : _switch(pin) {
    _pin = pin;
    _lastState = HIGH; // Assuming INPUT_PULLUP configuration
}

void LimitSwitch::begin(unsigned long debounceTime) {
    pinMode(_pin, INPUT_PULLUP);
    _switch.setDebounceTime(debounceTime);
}

void LimitSwitch::update() {
    _switch.loop();
}

uint8_t LimitSwitch::getState() {
    _lastState = _switch.getState();
    return _lastState;
}

bool LimitSwitch::stateChanged() {
    return _switch.isPressed() || _switch.isReleased();
}

bool LimitSwitch::isPressed() {
    return _switch.getState() == LOW; // For INPUT_PULLUP, LOW means pressed
}