#include <Arduino.h>

// You can declare functions at the top!

// Pin number for the LED
const int ledPin = 13; // Change this if your LED is connected to a different pin

const int inAPin = 19;
const int inBPin = 21;
const int pwmPin = 4;
const int enAPin = 22;
const int enBPin = 23;

void setup() {
  Serial.begin(9600);
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // ---------- LAST WORKING MOTOR CODE -------------
  // set motor control pins as outputs
  pinMode(inAPin, OUTPUT);
  pinMode(inBPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(enAPin, OUTPUT);
  pinMode(enBPin, OUTPUT);
  // ------------------------------------------------

}

void loop() {
  // LAST WORKING MOTOR CODE ---------
  // write pwm pin high 80% of time
  Serial.println("write analog pwm signal at 80%");
  digitalWrite(enAPin, HIGH);
  digitalWrite(enBPin, HIGH);
  digitalWrite(inAPin, HIGH);
  digitalWrite(inBPin, LOW);
  analogWrite(pwmPin, 255);  // 80% duty cycle (204/255 ≈ 0.8)

  Serial.println("delay 10 sec");
  delay(100);
  // ------------------

  
  // Serial.println("set 0 duty cycle");
  // digitalWrite(inAPin, LOW);
  // digitalWrite(inBPin, LOW);

  // Serial.println("delay 5 sec");
  // delay(5000);

  // Turn the LED on
  // digitalWrite(ledPin, HIGH);
  // delay(1000); // Wait for 1 second
  // Serial.println("LED is on\n");

  // Turn the LED off
  // digitalWrite(ledPin, LOW);
  // delay(1000); // Wait for 1 second
  // Serial.println("LED is on\n");

}

// and then put the function definitions later!