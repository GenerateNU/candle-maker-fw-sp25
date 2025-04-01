#include <Arduino.h>
#include <CMStateMachine.hpp>

//therm pin constant
const int fetPin = 15;

// sampling interval in ms
const int samplingInterval = 1000;

PID pid_controller(-127, 120, 55);



void test_task(void *parameter) {
  while (true) {
      Serial.println("Task 1 is running");
      vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  // pinMode(sourcePin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  pid_controller.Kp = 8.0f;
  pid_controller.Ki = 0.2f;
  pid_controller.Kd = 0.4f;
  pid_controller.T = static_cast<float>(samplingInterval) / 1000.0f;
  pid_controller.tau = 0.1f;
  
  // Serial.printf("Kp: %.2f | Ki: %.2f | Kd: %.2f\n",pid_controller.Kp, pid_controller.Ki, pid_controller.Kd);
  Serial.println("setup complete");
  delay(10);
  xTaskCreate(test_task, "test task", 128, NULL, 1, NULL);
}

void loop() {

  int startTime = millis();
  float out = pid_controller.update(45.0);
  int pid_out = static_cast<int>(out) + 127;
  analogWrite(fetPin, pid_out);
  delay(samplingInterval - 12);
  int endTime = millis();
  Serial.printf("loop took %d seconds\n", endTime - startTime);

  // // Serial.print("pinVoltage: ");
  // // Serial.print(pinVoltage);
  // // Serial.print(" rTherm: ");
  // // Serial.print(rTherm);
  // Serial.print(" temp: ");
}
