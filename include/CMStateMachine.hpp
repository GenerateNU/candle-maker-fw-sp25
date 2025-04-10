#ifndef CMSTATEMACHINE_HPP
#define CMSTATEMACHINE_HPP
// #include "CandleState.hpp"
#include "pid.hpp"
#include "solenoid.h"
#include <list>
#include <map>
// constants
//sampling interval for PID
const int samplingInterval = 200;

//pin for pid output 
const int fetPin = 15;

//bit depth of heating output
const int heatingResolution = 8;

//something
const int heatPwmChannel = 0;

// candle states enum
enum CANDLE_STATES {
    STANDBY,
    HEATING,
    DISPENSING,
    MIXING,
    WICK_PLACEMENT,
    COOLING,
    EJECTING
};

//needed to declare the hash map (defined)
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
    
private:
    CANDLE_STATES currentState{CANDLE_STATES::STANDBY};

    //handle to be able to delete task
    TaskHandle_t pidTaskHandle;
};

#endif