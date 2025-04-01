#include <Arduino.h>
#include <pid.hpp>

//therm pin constant
const int fetPin = 15;
const int samplingInterval = 200;

PID pid_controller(-127, 120, 55);

void pidTask(void *parameter) {
  const TickType_t xFreqeuncy = pdMS_TO_TICKS(100);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(true) {
    float output = pid_controller.update();
    vTaskDelayUntil(&xLastWakeTime, xFreqeuncy);
  }
}

void setup() {
  Serial.begin(115200);
  // pinMode(sourcePin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  pid_controller.Kp = 10.0f;
  pid_controller.Ki = 0.2f;
  pid_controller.Kd = 0.4f;
  pid_controller.T = static_cast<float>(samplingInterval) / 1000.0f;
  pid_controller.tau = 0.1f;
  
  Serial.printf("Kp: %.2f | Ki: %.2f | Kd: %.2f\n",pid_controller.Kp, pid_controller.Ki, pid_controller.Kd);
  Serial.println("setup complete");
  // xTaskCreate(pidTask, "PID Task", 1000, NULL, 1, NULL);
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

// and then put the function definitions later!