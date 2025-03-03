#include <Arduino.h>
#include <pid.hpp>
// You can declare functions at the top!

//therm pin constant
// const int sourcePin = 4;
const int fetPin = 19;


void setup() {
  Serial.begin(115200);
  // Set the LED pin as an output
  pinMode(THERM_PIN, INPUT);
  // pinMode(sourcePin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  Serial.println("setup complete");
  
}

void loop() {
  digitalWrite(fetPin, 255);
  delay(35);
  digitalWrite(fetPin, 0);
  delay(5);
  double temp = 0;

  // Serial.print("pinVoltage: ");
  // Serial.print(pinVoltage);
  // Serial.print(" rTherm: ");
  // Serial.print(rTherm);
  // Serial.print(" temp: ");
  // Serial.printf("%.2f deg C, %.2f deg F\n", temp, temp*1.8 + 32.0);
}

// and then put the function definitions later!