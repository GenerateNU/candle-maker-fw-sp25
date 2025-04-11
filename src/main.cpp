#include <Arduino.h>
#include <CMStateMachine.hpp>
#include "soc/ledc_reg.h"
#include "soc/ledc_struct.h"
#include "driver/ledc.h"


// screen shit
#include <SPI.h>
#include <TFT_eSPI.h>
#include "PortScreenHome.h"
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);  // Create display object


//therm pin constant


CMStateMachine stateMachine;

#ifndef LEDC_TIMER0_CONF_REG
#define LEDC_TIMER0_CONF_REG (DR_REG_LEDC_BASE + 0x08) // Base address + offset for Timer 0 config register
#endif

void verifyLEDCClockSource() {
    if (READ_PERI_REG(LEDC_TIMER0_CONF_REG) & (1 << 22)) {
      Serial.println("LEDC is using REF_TICK clock (1 MHz).");
  } else {
      Serial.println("LEDC is using APB clock (80 MHz).");
  }
}

void setLEDCClockSource() {
    uint32_t reg_val = READ_PERI_REG(LEDC_TIMER0_CONF_REG);
    reg_val |= (1 << 22); // Set bit 22 to use REF_TICK
    WRITE_PERI_REG(LEDC_TIMER0_CONF_REG, reg_val);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(5000);
  analogReadResolution(12);

  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(THERM_PIN, INPUT);
  // ledcSetup(0, 100, 8);
  // ledcAttachPin(13, 0);
  
  // Use ESP-IDF API to create low speed pwm
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 1000/samplingInterval,
    .clk_cfg = LEDC_USE_REF_TICK  // Directly specify REF_TICK clock
  };
  ledc_timer_config(&ledc_timer);

  ledc_channel_config_t ledc_channel = {
    .gpio_num = DRIVE_PIN,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = static_cast<ledc_channel_t>(heatPwmChannel),
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&ledc_channel);
  Serial.println("setup complete");
  verifyLEDCClockSource();
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

// #include <Arduino.h>
// #include <MotorEncoder.hpp>
// #include <MotorDriver.h>

// int RPWM1 = 4; // Right PWM pin
// int LPWM1 = 5; // Left PWM pin
// int encPinA1 = 6; // Encoder pin A
// int encPinB1 = 7; // Encoder pin B
// double gearRatio1 = 46.85; // Gear ratio
// MotorEncoder motor(RPWM1, LPWM1, encPinA1, encPinB1, gearRatio1); // Example pin numbers for RPWM, LPWM, encPinA, encPinB, gearRatio

// void setup() {
//   go();
  // Serial.begin(9600);
  // motor.setup();
  // //motor.runMotor(80, true);
  // //delay(1000); // Run the motor for 1 second
  // //motor.stopMotor(); // Stop the motor
  // motor.moveByRotation(80, true, 3); // Move clockwise for 1 rotation at 100% speed
  // delay(3000);
  // Serial.print(motor.currentPosition);

// }

// void loop() {
  // motor.moveByRotation(80, true, 1.0); // Move clockwise for 1 rotation at 100% speed
  // delay(1000);
  // motor.stopMotor(); // Stop the motor
// }
