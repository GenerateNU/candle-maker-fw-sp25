#ifndef CMSTATEMACHINE_HPP
#define CMSTATEMACHINE_HPP
#include "CandleState.hpp"
#include "pid.hpp"
#include <list>

// constants
//sampling interval for PID
const int samplingInterval = 200;



class StateMachine {

public:
    StateMachine() : cm_pid(nullptr) {}
    ~StateMachine() { delete cm_pid; }
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