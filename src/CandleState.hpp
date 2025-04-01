#pragma once
#include <map>
// #include "CMStateMachine.hpp"

enum CANDLE_STATES {
    STANDBY,
    HEATING,
    DISPENSING,
    MIXING,
    WICK_PLACEMENT,
    COOLING,
    EJECTING
};

// abstract implementation of stateMachine
class CMStateMachine;


class CandleState
{
public:
    virtual void enter(CMStateMachine* state) = 0;
    virtual void toggle(CMStateMachine* state) = 0;
    virtual void exit(CMStateMachine* state) = 0;
    virtual ~CandleState() {}
};

extern std::map<CANDLE_STATES, CANDLE_STATES> candleTransitions;