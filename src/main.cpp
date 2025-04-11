#include <Arduino.h>
#include <CMStateMachine.hpp>

// //therm pin constant


CMStateMachine stateMachine;


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(100);
  analogReadResolution(12);
  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(THERM_PIN, INPUT);
  ledcSetup(heatPwmChannel, 1000/samplingInterval, 8);
  ledcAttachPin(DRIVE_PIN, heatPwmChannel);
  Serial.println("setup complete");
  delay(10);
}

void loop() {

  int startTime = millis();
  stateMachine.go();
  int endTime = millis();
  stateMachine.nextState();
  Serial.printf("state took %d milliseconds\n", endTime - startTime);

}

// #include <Arduino.h>
// #include <MotorEncoder.hpp>
// #include <MotorDriver.h>

// int RPWM1 = 4; // Right PWM pin
// int LPWM1 = 5; // Left PWM pin
// int encPinA1 = 6; // Encoder pin A
// int encPinB1 = 7; // Encoder pin B
// double gearRatio1 = 46.85; // Gear ratio
// MotorEncoder motor(RPWM1, LPWM1, encPinA1, encPinB1, gearRatio1); // Example pin numbers for RPWM, LPWM, encPinA, encPinB, gearRatio

// void setup() {
//   go();
  // Serial.begin(9600);
  // motor.setup();
  // //motor.runMotor(80, true);
  // //delay(1000); // Run the motor for 1 second
  // //motor.stopMotor(); // Stop the motor
  // motor.moveByRotation(80, true, 3); // Move clockwise for 1 rotation at 100% speed
  // delay(3000);
  // Serial.print(motor.currentPosition);

// }

// void loop() {
  // motor.moveByRotation(80, true, 1.0); // Move clockwise for 1 rotation at 100% speed
  // delay(1000);
  // motor.stopMotor(); // Stop the motor
// }
