#include <Arduino.h>
#include <CMStateMachine.hpp>

//therm pin constant


CMStateMachine stateMachine;


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  pinMode(fetPin, OUTPUT);
  ledcSetup(heatPwmChannel, 1000/samplingInterval, 8);
  ledcAttachPin(fetPin, heatPwmChannel);
  Serial.println("setup complete");
  delay(10);
}

void loop() {

  int startTime = millis();
  stateMachine.go();
  int endTime = millis();
  stateMachine.nextState();
  Serial.printf("loop took %d milliseconds\n", endTime - startTime);

}
