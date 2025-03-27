// YourArduinoSketch.ino

// include your class header files here
#include "LEDBlinker.h"

LEDBlinker myLED(25); // Change 13 to the pin your LED is connected to
LEDBlinker myLED2(26); // If you wanted to add a second instance of the class

void setup() {
  // No setup needed for this example
  Serial.begin(9600);
}

void loop() {
  myLED.blink(500); // Blink every 500 milliseconds

  // need to add something else
}
