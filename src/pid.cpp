#include "pid.hpp"

float PID::readThermTemp() {
    float temp = 0;
    float pinVoltage = analogReadMilliVolts(THERM_PIN) / 1000.0;
    double rTherm = pinVoltage/(5.0f-pinVoltage) * 51000.0f;
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

PID::PID() {
    setpoint = 0.0f;
    integrator = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    limMin = 0.0f;
    limMax = 0.0f;
    Kp = 0.1f;

    out = 0.0f;
}

PID::PID(float minOut, float maxOut, float setpoint) {
    limMin = minOut;
    limMax = maxOut;
    setpoint = setpoint;
    integrator = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;

    out = 0.0f;
}



float PID::update(float setpoint) {
    //current temp is measurement
    float measurement = readThermTemp();
    float error = setpoint - measurement;

    // Proportional
    float proportional = Kp * error;

    // Integral term
    integrator = integrator + 0.5f * Ki * T * (error + prevError);

    // Integrator dynamic limits
    float limMaxInt, limMinInt;
    
    //anti-windup in integrator - creates a maximum value for integrator term
    if (limMax > proportional) {
        limMaxInt = limMax - proportional;
    }
    else {
        limMaxInt = 0.0f;
    }

    if (limMin < proportional) {
        limMinInt = limMin - proportional;
    }
    else {
        limMinInt = 0.0f;
    }

    if (integrator < limMinInt) {
        integrator = limMinInt;
    } 
    else if (integrator > limMaxInt) {
        integrator  = limMaxInt;
    }

    //Derivative term (bandlimited differentiator)
    differentiator = (2.0f * Kd * (measurement - prevMeasurement)
    + (2.0f * tau - T) * differentiator)
    / (2.0f * tau * T);

    //sum p, i, and d
    out = proportional + integrator + differentiator;

    if (out > limMax) {
        out = limMax;
    }
    else if (out < limMin) {
        out = limMin;
    }
    
    prevError = error;
    prevMeasurement = measurement;
    
    return out;
}

PID::~PID() {}