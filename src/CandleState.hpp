#pragma once
#include <map>
#include "CMStateMachine.hpp"
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

std::map<CANDLE_STATES, CANDLE_STATES> candleTransitions = {
{CANDLE_STATES::STANDBY, CANDLE_STATES::HEATING},
{CANDLE_STATES::HEATING, CANDLE_STATES::DISPENSING},
{CANDLE_STATES::DISPENSING, CANDLE_STATES::MIXING},
{CANDLE_STATES::MIXING, CANDLE_STATES::WICK_PLACEMENT},
{CANDLE_STATES::WICK_PLACEMENT, CANDLE_STATES::COOLING},
{CANDLE_STATES::COOLING, CANDLE_STATES::EJECTING},
{CANDLE_STATES::EJECTING, CANDLE_STATES::STANDBY}
};