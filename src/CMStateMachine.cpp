#include "CMStateMachine.hpp"

// StateMachine::StateMachine() {

// }

int StateMachine::go() {
    switch (this->currentState) {
        case CANDLE_STATES::STANDBY:
            //screen on,
            //poll user input or make it an interrupt,
            this->currentState = candleTransitions[this->currentState];
            break;
        case CANDLE_STATES::HEATING:
            
    }
    return 0;
}
