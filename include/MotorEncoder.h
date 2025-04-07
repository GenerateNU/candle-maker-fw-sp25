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
    void moveByRotation(int speed, bool direction, double numRotations, double gearRatio);
    void goHome(int speed);
    volatile int currentPosition;
    int _encPinA;
    int _encPinB;
    void setup(int encPinA, int encPinB);
    int previousA;
    int previousB;
    static int triggeredPin;
    static int triggeredMotor;
    static MotorEncoder* instance[4]; // Array of pointers to MotorEncoder instances
    
    

    private:
    double _targetPosition;
    //int previousEncA;
    //int previousEncB;
    //double targetPosition;
    double _gearRatio;

    

    
};

#endif