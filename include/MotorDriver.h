#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

class MotorDriver {
  public:
    MotorDriver(int pwmPin, int inAPin, int inBPin);
    void runMotor(int speed, bool direction); // speed in %, direction: true for clockwise, false for counter-clockwise
    void stopMotor();
    void runForTime(int speed, bool direction, int time);
    int _speed;
    bool _direction;
    bool running = false;

  protected:
    int _pwmPin;
    int _inAPin;
    int _inBPin;
    int _speedpercent;
    
   
};

#endif