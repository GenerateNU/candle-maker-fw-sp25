#include <NewMotorDriver.h>


NewMotorDriver::NewMotorDriver(int RPWM, int LPWM) {
  _RPWM = RPWM;
  _LPWM = LPWM;
  pinMode(_RPWM, OUTPUT);
  pinMode(_LPWM, OUTPUT);
}

void NewMotorDriver::runMotor(int speed, bool direction) { 
    //Serial.println("Motor running");
 _speedpercent = speed; 
 _speed = _speedpercent*255/100;// Convert percentage to PWM value (0-255)
 _direction = direction;
 running = true;

    if (_direction){
        analogWrite(_RPWM, 204);
        // digitalWrite(_LPWM, LOW);
        // delay(100);
        analogWrite(_RPWM, _speed);
    }
        
    else if(!_direction){
       digitalWrite(_RPWM, LOW);
        // analogWrite(_LPWM, 204);
        // delay(100);
        analogWrite(_LPWM, _speed);
      
    }
}

void NewMotorDriver::stopMotor() {
    analogWrite(_RPWM, 0);
    analogWrite(_LPWM, 0);
    running = false;
}

void NewMotorDriver::runForTime(int speed, bool direction, int time) {
    runMotor(speed, direction);
    delay(time); // Run for specified time
    stopMotor(); // Stop motor after time is up
}