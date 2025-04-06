#ifndef MotoEncoder_h
#define MotoEncoder_h

#include "MotorDriver.h"
#include "Arduino.h"
#include "iostream" // For std::cout

class MotorEncoder : public MotorDriver {
  public:
    MotorEncoder(int pwmpin, int inAPin, int inBPin,  int encPinA, int encPinB, int gearRatio);
    static void encoderISR();
    int getCurrentPosition();
    void goToTargetPosition(int speed, bool direction, int targetPosition);
    void moveByAmount(int speed, bool direction, int moveAmount);
    void goHome(int speed);
    volatile int currentPosition;
    int _encPinA;
    int _encPinB;
    void setup(int encPinA, int encPinB);
    static int previousPin[4][2];
    static int triggeredPin;
    static int triggeredMotor;
    static MotorEncoder* instance[4]; // Array of pointers to MotorEncoder instances
    

    private:
    int _targetPosition;
    //int previousEncA;
    //int previousEncB;
    int moveAmount;
    int gearRatio;
    

    

    
};

#endif