#include <MotorEncoder.hpp>


 // Declare the static member
MotorEncoder* MotorEncoder::instance[4] = {nullptr}; // Array to hold instances of MotorEncoder
// MotorEncoder::MotorEncoder() : NewMotorDriver() { // Default constructor for MotorEncoder
//   currentPosition = 0;
//   _encPinA = 0;
//   _encPinB = 0;
//   _gearRatio = 1; // Default gear ratio
// }
MotorEncoder::MotorEncoder (int RPWM, int LPWM, int encPinA, int encPinB, int gearRatio) : NewMotorDriver(RPWM, LPWM) { // Initialize MotorDriver with required parameters
  int currentPosition = 0;
  _encPinA = encPinA;
  _encPinB = encPinB;
  _gearRatio = gearRatio;
 
  pinMode(_encPinA, INPUT);
  pinMode(_encPinB, INPUT);
  
  int motorcount = 0;
  instance[motorcount] = this; // Assign the current instance to the static member
  motorcount++;
  previousA = digitalRead(_encPinA);
  previousB = digitalRead(_encPinB);

}

void MotorEncoder::setup() {
_encPinA = this->_encPinA;
_encPinB = this->_encPinB;
  attachInterrupt(digitalPinToInterrupt(_encPinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_encPinB), encoderISR, CHANGE);
  //Serial.println(currentPosition); 
  Serial.println("MotorEncoder setup complete");
 
}


void MotorEncoder::encoderISR() {
    int triggeredPin = -1;
    int triggeredMotor = -1;
    for (int i = 0; i < 4; i++) {
        if (instance[i]!= nullptr && digitalRead(instance[i]->_encPinA) != instance[i]->previousA) {
                triggeredMotor = i;
                triggeredPin = 0;
                instance[i]->previousA = digitalRead(instance[i]->_encPinA);
        }
        else if (instance[i]!= nullptr && digitalRead(instance[i]->_encPinB) != instance[i]->previousB) {
                triggeredMotor = i;
                triggeredPin = 1;
                instance[i]->previousB = digitalRead(instance[i]->_encPinB);
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
  Serial.println("current position: ");
  Serial.println(currentPosition);
  return currentPosition;

}
void MotorEncoder::goToTargetPosition(int speed, bool direction, int targetPosition) {
  _speed = speed;
  _direction = direction;
  _targetPosition = targetPosition;
  Serial.println(currentPosition);
  Serial.println(targetPosition);
  runMotor(_speed, _direction);
  if(!_direction){
    while(currentPosition < _targetPosition);
    stopMotor();
  }
  else{
    while(currentPosition > _targetPosition);
    stopMotor();
  }
  
}
void MotorEncoder::moveByRotation(int speed, bool direction, double numRotations) {
_direction = direction;
_speed = speed;
_gearRatio = this->_gearRatio;

  if(!_direction){
    _targetPosition = currentPosition + numRotations*_gearRatio*48; // 48 counts per revolution 
    Serial.println(_gearRatio);
  }
  else{
    _targetPosition = currentPosition - numRotations*_gearRatio*48; // 48 counts per revolution 
  }
  Serial.println("target position: ");
  Serial.println(_targetPosition);
  goToTargetPosition(_speed, _direction, _targetPosition);
  
}

void MotorEncoder::goHome(int speed) {
  _speed = speed;
  if(currentPosition > 0){
    goToTargetPosition(80, true, 0); // Move counter-clockwise to home position
  }
  else{
    goToTargetPosition(80, false, 0); // Move clockwise to home position
  }
  
  Serial.println("Motor is at home position.");
}

void MotorEncoder::resetHome() {
  currentPosition = 0; // Reset the current position to 0
  Serial.println("Home position reset");
}
