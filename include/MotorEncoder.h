#ifndef MotoEncoder_h
#define MotoEncoder_h

#include "NewMotorDriver.h"
#include "Arduino.h"

class MotorEncoder : public NewMotorDriver {
  public:
    MotorEncoder(int RPWM, int LPWM, int encPinA, int encPinB, int gearRatio);
    static void encoderISR();
    int getCurrentPosition();
    void goToTargetPosition(int speed, bool direction, int targetPosition);
    void moveByRotation(int speed, bool direction, double numRotations);
    void goHome(int speed);
    void resetHome();
    volatile int currentPosition;
    int _encPinA;
    int _encPinB;
    void setup();
    int previousA;
    int previousB;
    static int triggeredPin;
    static int triggeredMotor;
    static MotorEncoder* instance[4]; // Array of pointers to MotorEncoder instances
    double _gearRatio;

    

    private:
    int _targetPosition = 0;

    
    

    
};

#endif