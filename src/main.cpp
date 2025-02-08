#include <Arduino.h>

// You can declare functions at the top!

//therm pin constant
const int thermistorPin = 35;
const int sourcePin = 4;
const float A1[2]	= {0.003353823,	0.003354016};
const float B[2] = {0.000261843,	0.00026056};
const float C1[2]	= {3.92E-06,	3.13E-06};
const float D1[2] = {1.40E-07,	9.84E-08};



void setup() {
  Serial.begin(115200);
  // Set the LED pin as an output
  pinMode(thermistorPin, INPUT);
  pinMode(sourcePin, OUTPUT);
  Serial.println("setup complete");

}

void loop() {
  double temp = 0;
  digitalWrite(sourcePin, 255);
  delayMicroseconds(10000);
  double pinVoltage = analogReadMilliVolts(thermistorPin) / 1000.0;
  Serial.print("pinVoltage: ");
  Serial.print(pinVoltage);
  double rTherm = 183810.0/pinVoltage - 55700.0;
  Serial.print(" rTherm: ");
  Serial.print(rTherm);
  // if temp is under 25 we know resistance will be greater than 30000 ohm
  if (rTherm > 30000.0) {
    temp = 1/(A1[0]+B[0]*log(rTherm/30000.0)+C1[0]*pow(log(rTherm/30000.0),2)+D1[0]*pow(log(rTherm/30000.0),3))-273.15;
  }
  else {
    temp = 1/(A1[1]+B[1]*log(rTherm/30000.0)+C1[1]*pow(log(rTherm/30000.0),2)+D1[1]*pow(log(rTherm/30000.0),3))-273.15;
  }
  Serial.print(" temp: ");
  Serial.printf("%.2f deg C, %.2f deg F\n", temp, temp*1.8 + 32.0);
  digitalWrite(sourcePin, 0);
  sleep(10);
}

// and then put the function definitions later!