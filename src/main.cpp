// YourArduinoSketch.ino

#include "LEDBlinker.h"

LEDBlinker myLED(25); // Change 13 to the pin your LED is connected to
LEDBlinker myLED2(26);

void setup() {
  // No setup needed for this example
}

void loop() {
  myLED.blink(500); // Blink every 500 milliseconds

  // need to add something else
}











// #include <Arduino.h>
// #include "ExClass.h" // Include your ExClass header

// // Create an instance of the ExClass
// // ExClass myDevice;

// // Pin number for the LED
// // const int ledPin = 12;
// uint8_t ledPin = 25;

// void setup() {
//   Serial.begin(9600);

//   ExClass myDevice;

//   // Set up pins in the ExClass object
//   // myDevice.setControlPins(2, 3); // Example motor pins
//   // myDevice.setInputPin(4); // Example input pin
//   myDevice.setLedPin(ledPin); // Set the LED pin
//   // pinMode(ledPin, OUTPUT); // Set the LED pin as output
// }

// void loop() {
//   // Turn LED on and off
//   // myDevice.turnLedOn();
//   // delay(1000);
//   // Serial.println("LED on");
//   // myDevice.turnLedOff();
//   // delay(1000);
//   // Serial.println("LED off");
//   digitalWrite(ledPin, HIGH);
//   delay(1000);
//   Serial.println("LED on");
//   digitalWrite(ledPin, LOW);
//   delay(1000);
//   Serial.println("LED off");

//   // Example: Read an input and control a motor
//   // bool inputState = myDevice.readInput();
//   // if (inputState) {
//   //   myDevice.startMotor(true); // Start motor forward
//   //   Serial.println("Motor forward.");
//   // } else {
//   //   myDevice.startMotor(false); // Start motor reverse
//   //   Serial.println("Motor reverse.");
//   // }

//   // delay(100); // Small delay to prevent rapid input reading
// }