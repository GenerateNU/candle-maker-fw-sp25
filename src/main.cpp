//#include <Arduino.h>
/**
// Define motor control pins for VNH5019
const int pwmPin = 4;   // PWM input
const int inAPin = 19;  // Direction input 1
const int inBPin = 21;  // Direction input 2
//const int enPin = 22;   // Status flag output (not needed for basic operation)
//const int csPin = 23;   // Current sense pin (optional)
const int encPinA = 18;
const int encPinB = 5;

// Motor control parameters
int initialSpeed = 204; // Initial speed (80% duty cycle)
int pwmSpeed = initialSpeed;  // 80% duty cycle (204/255)

// Motor parameters
//int targetPosition = 8245.81; // 1 rev for 172:1 geared motor (171.79*48counts*3revs =)
int targetPosition = 8245.81;
volatile int currentPosition = 0; // Current encoder count
// Function to read the encoder A signal and update position
int previousA = digitalRead(encPinA);
int previousB = digitalRead(encPinB);

void encoderISR() {
  if(previousA != digitalRead(encPinA)){
    previousA = digitalRead(encPinA);
    if ((digitalRead(encPinA) == HIGH && digitalRead(encPinB) == LOW) || (digitalRead(encPinA) == LOW && digitalRead(encPinB) == HIGH)) {
      currentPosition++; // Clockwise
    }
    else {
     currentPosition--; // Counter-clockwise
    }
  }
  else if (previousB != digitalRead(encPinB)){
    previousB = digitalRead(encPinB);
    if ((digitalRead(encPinA) == LOW && digitalRead(encPinB) == LOW) || (digitalRead(encPinA) == HIGH && digitalRead(encPinB) == HIGH)) {
      currentPosition++; // Clockwise
    }
    else {
     currentPosition--; // Counter-clockwise
    }
  }

}
// Setup function
void setup() {
    Serial.begin(9600);

    // Set motor control pins as outputs
    pinMode(inAPin, OUTPUT);
    pinMode(inBPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    //pinMode(enPin, INPUT);  // Read status flag (optional)
    //pinMode(csPin, INPUT);  // Read current sense (optional)
    // Initialize encoder pins
    pinMode(encPinA, INPUT);
    pinMode(encPinB, INPUT);
  
    // Attach interrupt to encoder pin A for counting
    attachInterrupt(digitalPinToInterrupt(encPinA), encoderISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encPinB), encoderISR, CHANGE);
  
  

    Serial.println("Pololu VNH5019 Motor Driver Initialized");
}

// Loop function
void loop() {
    // Move motor forward
    Serial.println("Motor moving forward at 80% speed");
    digitalWrite(inAPin, HIGH);
    digitalWrite(inBPin, LOW);
    analogWrite(pwmPin, pwmSpeed);
    //delay(5000);  // Run for 5 seconds
  

   int slowdown = 2000;
   int error;
   int kp;

   if (abs(currentPosition) >= abs(targetPosition) - slowdown) {
      error = abs(targetPosition) - abs(currentPosition);
      kp = pwmSpeed/slowdown; // Proportional gain
      if (error*kp > 50){
      pwmSpeed = error*kp;
      }
      else{
        pwmSpeed = 50;
      }
    }

    if (abs(currentPosition) >= abs(targetPosition)) {
      // Stop the motor once the target is reached
      digitalWrite(inAPin, LOW);
      digitalWrite(inBPin, LOW);
      analogWrite(pwmPin, 0); // Stop motor
      Serial.print("Current Position: ");
      Serial.println(currentPosition);
      while (1); // Stop the program (infinite loop after motor stops)
    }

  // Print current position for debugging
  Serial.print("Current Position: ");
  Serial.println(currentPosition);
}
*/



#include <MotorEncoder.h>
#include <Arduino.h>

MotorEncoder motor(19, 21, 5, 18, 171.79); // Initialize motor driver with PWM and direction pins
//MotorDriver motor1(4, 19, 21); // Initialize motor driver with PWM and direction pins
int _motorON = 0;
int _motorOFF = 1;
enum motorState { MOTOR_OFF, MOTOR_ON, MOTOR_DONE };
motorState state = MOTOR_OFF;
bool finished = false;
void setup() {
    Serial.begin(9600);
    motor.setup(); // Setup encoder pins
    // motor.moveByRotation(80, true, 1, 171.79); // Run motor at 80% speed in counter-clockwise direction
    // delay(3000);
    // motor.getCurrentPosition(); // Get current position
    // delay(3000);
    // motor.runMotor(80, true); // Run motor at 80% speed in clockwise direction  
    // delay(3000);
    // motor.stopMotor(); // Stop motor

}
void loop() {
  
  if (state == MOTOR_OFF){
     state = MOTOR_ON;
     motor.moveByRotation(80, true, 1); // Run motor at 80% speed in counter-clockwise direction
     delay(500); 
     motor.moveByRotation(80, false, 0.5); 
     delay(500);
     motor.goToTargetPosition(80, false, -4500); // Move to target position at 80% speed
     delay(500);
     motor.goHome(80); // Move motor to home position at 80% speed
     delay(500);
  }
  else if (state == MOTOR_ON) {
     state = MOTOR_DONE;
     delay(3000); // Wait for 3 second
     motor.getCurrentPosition(); // Get current position
  } 
  
}


// #include <Arduino.h>
// #include <CMStateMachine.hpp>
















/** 



#include <Arduino.h>
#include "MCPManager.h"

#define LED_PIN 6

MCPManager expander0(0x20); // A0-A2 = 000
MCPManager expander1(0x21); // A0-A2 = 001

//therm pin constant


//CMStateMachine stateMachine;


void setup() {
  Serial.begin(9600); // 115200

    Serial.println("Starting MCP23017 Expanders...");

    if (!expander0.begin()) {
        Serial.println("Failed to init expander 0");
        while (1);
    }
    if (!expander1.begin()) {
        Serial.println("Failed to init expander 1");
        while (1);
    }

    expander0.setupPin(LED_PIN, OUTPUT);
    expander1.setupPin(LED_PIN, OUTPUT);

    Serial.println("Expanders ready.");
  
  // while (!Serial) {}
  // pinMode(fetPin, OUTPUT);
  // ledcSetup(heatPwmChannel, 1000/samplingInterval, 8);
  // ledcAttachPin(fetPin, heatPwmChannel);
  // Serial.println("setup complete");
  // delay(10);
  
}

void loop() {

  expander0.togglePin(LED_PIN);
    expander1.togglePin(LED_PIN);
    delay(500);
  


  
  // int startTime = millis();
  // stateMachine.go();
  // int endTime = millis();
  // stateMachine.nextState();
  // Serial.printf("loop took %d milliseconds\n", endTime - startTime);
  
}

*/







  