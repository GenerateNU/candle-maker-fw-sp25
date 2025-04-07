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

    if (_direction){
        digitalWrite(_inAPin, HIGH);
        digitalWrite(_inBPin, LOW);
        analogWrite(_pwmPin, _speed);
        //Serial.println("clockwise");
        //std::cout <<"Motor running clockwise at speed: " << _speedpercent << "% (" <<  _speed << "/255)" << std::endl;
    }
        
    else if(!_direction){
        digitalWrite(_inAPin, LOW);
        digitalWrite(_inBPin, HIGH);
        analogWrite(_pwmPin, _speed);
        //Serial.println("counter-clockwise" );
        //Serial.print ( _speedpercent );
        //+ "% (" + _speed + "/255 )");
        //std::cout <<"Motor running counter-clockwise at speed: " << _speedpercent << "% (" <<  _speed << "/255)" << std::endl;
    }
}

void MotorDriver::stopMotor() {
    digitalWrite(_inAPin, LOW);
    digitalWrite(_inBPin, LOW);
    analogWrite(_pwmPin, 0); // Stop motor
    //std::cout << "Motor stopped" << std::endl;
}