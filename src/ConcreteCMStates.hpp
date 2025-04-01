#pragma once
#include "candleState.hpp"
#include "CMStateMachine.hpp"

class CandleStandby : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
CandleStandby() {}
    // copy constructor
    CandleStandby(const CandleStandby& other);
    CandleStandby& operator=(const CandleStandby& other);
};

class CandleHeating : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
    CandleHeating() {}
    // copy constructor
    CandleHeating(const CandleHeating& other);
    CandleHeating& operator=(const CandleHeating& other);
};

class CandleDispensing : public CandleState 
{
public:
    void enter(CMStateMachine* state) {}
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
    CandleDispensing() {}
    // copy constructor
    CandleDispensing(const CandleDispensing& other);
    CandleDispensing& operator=(const CandleDispensing& other);
};

class CandleMixing : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
CandleMixing() {}
    // copy constructor
    CandleMixing(const CandleMixing& other);
    CandleMixing& operator=(const CandleMixing& other);
};

class CandleWickPlacement : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
CandleWickPlacement() {}
    // copy constructor
    CandleWickPlacement(const CandleWickPlacement& other);
    CandleWickPlacement& operator=(const CandleWickPlacement& other);
};


class CandleCooling : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
CandleCooling() {}
    // copy constructor
    CandleCooling(const CandleCooling& other);
    CandleCooling& operator=(const CandleCooling& other);
};


class CandleEjecting : public CandleState 
{
public:
    void enter(CMStateMachine* state);
    void toggle(CMStateMachine* state);
    void exit(CMStateMachine* state);
    static CandleState& getInstance;

private:
CandleEjecting() {}
    // copy constructor
    CandleEjecting(const CandleEjecting& other);
    CandleEjecting& operator=(const CandleEjecting& other);
};
