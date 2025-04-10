#include <Arduino.h>
#include <CMStateMachine.hpp>

//therm pin constant


CMStateMachine stateMachine;


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
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
