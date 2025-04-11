#ifndef NewMotorDriver_h
#define NewMotorDriver_h

#include "Arduino.h"

class NewMotorDriver {
  public:
    NewMotorDriver(int RPWM, int LPWM);
    void runMotor(int speed, bool direction); // speed in %, direction: true for clockwise, false for counter-clockwise
    void stopMotor();
    void runForTime(int speed, bool direction, int time);
    int _speed;
    bool _direction;
    bool running = false;

  protected:
    int _RPWM;
    int _LPWM;
    int _speedpercent;
    
   
};

#endif