#include "pid.hpp"

float PID::readThermTemp() {
    float temp = 0;
    float pinVoltage = analogReadMilliVolts(THERM_PIN) / 1000.0;
    double rTherm = pinVoltage/(3.3f-pinVoltage) * 51000.0f;
    // if temp is under 25 we know resistance will be greater than 30000 ohm
    if (rTherm > 30000.0) {
        temp = 1/(A1[0]+B[0]*log(rTherm/30000.0)+C1[0]*pow(log(rTherm/30000.0),2)+D1[0]*pow(log(rTherm/30000.0),3))-273.15;
        Serial.println(temp);
    }
    else {
        temp = 1/(A1[1]+B[1]*log(rTherm/30000.0)+C1[1]*pow(log(rTherm/30000.0),2)+D1[1]*pow(log(rTherm/30000.0),3))-273.15;
        Serial.println(temp);
    }
    return temp;
}

float PID::get_error() {
    return this->error;
}

float PID::get_prevError() {
    return this->prevError;
}
PID::PID() {
    setpoint = 0.0f;
    integrator = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    limMin = 0.0f;
    limMax = 0.0f;
    limMaxInt = 0.0f;
    limMinInt = 0.0f;
    Kp = 0.0f;
    Ki = 0.0f;
    Kd = 0.0f;
    out = 0.0f;
}

PID::PID(float minOut, float maxOut, float setpoint) {
    limMin = minOut;
    limMax = maxOut;
    limMaxInt = maxOut;
    limMinInt = minOut;
    setpoint = setpoint;
    integrator = 0.0f;
    differentiator = 0.0f;
    Kp = 0.1f;
    Ki = 0.1f;
    Kd = 0.01f;
    prevMeasurement = 0.0f;
    out = 0.0f;
    tau = 0.001f;
}



float PID::update(float setpoint) {
    //current temp is measurement
    // unsigned long startTime = micros();
    float measurement = readThermTemp();
    Serial.printf("%.2f deg C, %.2f deg F\n", measurement, measurement*1.8 + 32.0);

    error = setpoint - measurement;
    Serial.printf("Error: %.4f |", error);

    // Proportional term
    float proportional = Kp * error;
    Serial.printf("Proportional: %.4f |", proportional);

    // Integral term
    integrator = integrator + 0.5f * Ki * T * (error + prevError);    
    //anti-windup in integrator - creates a maximum value for integrator term

    if (integrator < limMinInt) {
        integrator = limMinInt;
    } 
    else if (integrator > limMaxInt) {
        integrator  = limMaxInt;
    }
    Serial.printf("Integrator: %.4f | ", integrator);


    //Derivative term (bandlimited differentiator)
    differentiator = (2.0f * Kd * (measurement - prevMeasurement)
    + (2.0f * tau - T) * differentiator
    / (2.0f * tau + T));

    Serial.printf("Differentiator: %.4f |", differentiator);

    //sum p, i, and d
    out = proportional + integrator + differentiator;
    if (out > limMax) {
        out = limMax;
    }
    else if (out < limMin) {
        out = limMin;
    }
    Serial.printf("%0.5f\n", out);

    prevError = error;
    prevMeasurement = measurement;
    // unsigned long endTime = micros();
    // Serial.printf("Time to execute one iteration of loop: %2f\n", endTime - startTime);
    return out;
}

PID::~PID() {}