#include <Arduino.h>
#include <CMStateMachine.hpp>

//therm pin constant
const int fetPin = 15;


CMStateMachine stateMachine;


void test_task(void *parameter) {
  while (true) {
      Serial.println("Task 1 is running");
      vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  pinMode(fetPin, OUTPUT);
  
  Serial.println("setup complete");
  delay(10);
  xTaskCreate(test_task, "test task", 2048, NULL, 1, NULL);
}

void loop() {

  int startTime = millis();
  stateMachine.go();
  int endTime = millis();
  stateMachine.nextState();
  Serial.printf("loop took %d milliseconds\n", endTime - startTime);

}
