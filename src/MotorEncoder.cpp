#include <MotorEncoder.h>


 // Declare the static member
MotorEncoder* MotorEncoder::instance[4] = {nullptr}; // Array to hold instances of MotorEncoder
int MotorEncoder::previousPin[4][2]; // Initialize previousPin array to store previous states of encoders

MotorEncoder::MotorEncoder (int pwmpin, int inAPin, int inBPin, int encPinA, int encPinB, int gearRatio) : MotorDriver(pwmpin, inAPin, inBPin) { // Initialize MotorDriver with required parameters
  _encPinA = encPinA;
  _encPinB = encPinB;
 
  pinMode(_encPinA, INPUT);
  pinMode(_encPinB, INPUT);
  
  int motorcount = 0;
  instance[motorcount] = this; // Assign the current instance to the static member
  motorcount++;
}

void MotorEncoder::setup(int encPinA, int encPinB) {

  attachInterrupt(digitalPinToInterrupt(encPinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encPinB), encoderISR, CHANGE);
  Serial.println(currentPosition); 
 
}

void MotorEncoder::encoderISR() {
    int triggeredPin = -1;
    int triggeredMotor = -1;
    for (int i = 0; i < 4; i++) {
        if (instance[i]!= nullptr && instance[i]->_encPinA != previousPin[i][0]) {
                triggeredMotor = i;
                triggeredPin = 0;
                previousPin[i][0] = digitalRead(instance[i]->_encPinA);
        }
        else if (instance[i]!= nullptr && instance[i]->_encPinB != previousPin[i][1]) {
                triggeredMotor = i;
                triggeredPin = 1;
                previousPin[i][1] = digitalRead(instance[i]->_encPinB);
        }
    }
    if (triggeredPin == 0){
        if ((digitalRead(instance[triggeredMotor]->_encPinA) == HIGH && digitalRead(instance[triggeredMotor]->_encPinB) == LOW) || (digitalRead(instance[triggeredMotor]->_encPinA) == LOW && digitalRead(instance[triggeredMotor]->_encPinB) == HIGH)) {
            instance[triggeredMotor]->currentPosition++; // Clockwise
        }
        else {
            instance[triggeredMotor]->currentPosition--; // Counter-clockwise
        }
    }
    else if (triggeredPin == 1){
        if ((digitalRead(instance[triggeredMotor]->_encPinA) == LOW && digitalRead(instance[triggeredMotor]->_encPinB) == LOW) || (digitalRead(instance[triggeredMotor]->_encPinA) == HIGH && digitalRead(instance[triggeredMotor]->_encPinB) == HIGH)) {
            instance[triggeredMotor]->currentPosition++; // Clockwise
        }
        else {
            instance[triggeredMotor]->currentPosition--; // Counter-clockwise
        }
    }

}

int MotorEncoder::getCurrentPosition() {
  return currentPosition;

}