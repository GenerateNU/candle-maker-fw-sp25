#include <MotorDriver.h>


MotorDriver::MotorDriver(int pwmPin, int inAPin, int inBPin) {
  _pwmPin = pwmPin;
  _inAPin = inAPin;
  _inBPin = inBPin;
  pinMode(_pwmPin, OUTPUT);
  pinMode(_inAPin, OUTPUT);
  pinMode(_inBPin, OUTPUT);
}

void MotorDriver::runMotor(int speed, bool direction) { 
    //Serial.println("Motor running");
 _speedpercent = speed; 
 _speed = _speedpercent*255/100;// Convert percentage to PWM value (0-255)
 _direction = direction;
 running = true;

    if (_direction){
        digitalWrite(_inAPin, HIGH);
        digitalWrite(_inBPin, LOW);
        analogWrite(_pwmPin, 204);
        delay(10);
        analogWrite(_pwmPin, _speed);
    }
        
    else if(!_direction){
        digitalWrite(_inAPin, LOW);
        digitalWrite(_inBPin, HIGH);
        analogWrite(_pwmPin, 204);
        delay(10);
        analogWrite(_pwmPin, _speed);
      
    }
}

void MotorDriver::stopMotor() {
    digitalWrite(_inAPin, LOW);
    digitalWrite(_inBPin, LOW);
    analogWrite(_pwmPin, 0); // Stop motor
    running = false;
}

void MotorDriver::runForTime(int speed, bool direction, int time) {
    runMotor(speed, direction);
    delay(time); // Run for specified time
    stopMotor(); // Stop motor after time is up
}