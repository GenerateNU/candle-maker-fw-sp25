#include <Arduino.h>
#ifndef PID_HPP
#define PID_HPP
#define THERM_PIN 31

const float A1[2]	= {0.003353823,	0.003354016};
const float B[2] = {0.000261843,	0.00026056};
const float C1[2]	= {3.92E-06,	3.13E-06};
const float D1[2] = {1.40E-07,	9.84E-08};

class PID {
    private:

        //controller memory
        float integrator;
        float prevError;
        float differentiator;
        float prevMeasurement;
    
    public:
        // proportional gain
        float Kp;

        // integrator gain
        float Ki;

        //derivative gain
        float Kd;
        
        // time constant for lowpass filter
        float tau;
    
        //sample time (s)
        float T;
        float setpoint;
        float limMin;
        float limMax;
        float out;

        float update(float setpoint);
        float readThermTemp();
        PID();
        PID(float minOut, float maxOut, float setpoint);
        ~PID();   
};
#endif