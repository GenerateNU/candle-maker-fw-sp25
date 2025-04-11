#ifndef CMSTATEMACHINE_HPP
#define CMSTATEMACHINE_HPP
#define DRIVE_PIN 7
#include "pid.hpp"
#include "LCD.h"
#include <list>
#include <map>

// constants
//sampling interval for PID
const int samplingInterval = 200;
const int heatingResolution = 8;
const int heatPwmChannel = 1;

enum CANDLE_STATES {
    STANDBY,
    HEATING,
    DISPENSING,
    MIXING,
    WICK_PLACEMENT,
    COOLING,
    EJECTING
};

extern std::map<CANDLE_STATES,CANDLE_STATES> candleTransitions;
class CMStateMachine {

public:
    CMStateMachine();
    ~CMStateMachine() { delete cm_pid; }
    //this method is called to go to the next state as defined by the state map candleTransitions.
    void nextState();
    void setState(CANDLE_STATES newState);
    int go();
    PID* cm_pid;
    // LCDScreen* lcd_screen;
private:
    CANDLE_STATES currentState{CANDLE_STATES::STANDBY};

    //handle to be able to delete task
    TaskHandle_t pidTaskHandle;
};

#endif