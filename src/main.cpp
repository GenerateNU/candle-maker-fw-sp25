#include <Arduino.h>

// You can declare functions at the top!

//therm pin constant
const int thermistorPin = 35;

void setup() {
  Serial.begin(115200);
  // Set the LED pin as an output
  pinMode(thermistorPin, INPUT);
  analogReadResolution(12);
  Serial.println('setup complete');
}

void loop() {
  u_int8_t thermValue = analogRead(thermistorPin);
  Serial.println(thermValue);

}

// and then put the function definitions later!