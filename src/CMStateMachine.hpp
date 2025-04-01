#ifndef CMSTATEMACHINE_HPP
#define CMSTATEMACHINE_HPP
#include "candleState.hpp"



class StateMachine {

public:
    StateMachine();
    void nextState();
    void toggle();
    void setState();
    int go();
private:
    CANDLE_STATES currentState{CANDLE_STATES::STANDBY};
   
};

#endif