#include <Arduino.h>
#include <CMStateMachine.hpp>

// screen shit
#include <SPI.h>
#include <TFT_eSPI.h>
#include "PortScreenHome.h"
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);  // Create display object


//therm pin constant


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
  
  // init TFT screen
  tft.init();             // Initialize the display
  tft.setRotation(0);     // Set rotation (adjust as necessary)

  tft.fillScreen(TFT_BROWN); // Background color

  // displayHeatingScreen(tft);
  delay(2);
  // displayBasicScreen(tft);
  // delay(5);
}

void loop() {

  int startTime = millis();
  stateMachine.go();
  int endTime = millis();
  stateMachine.nextState();
  Serial.printf("state took %d milliseconds\n", endTime - startTime);

}
