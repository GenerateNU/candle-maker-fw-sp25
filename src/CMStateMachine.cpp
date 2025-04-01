#include "CMStateMachine.hpp"

//tasks
void pidTask(void *parameter) {
    StateMachine* stateMachine = static_cast<StateMachine*>(parameter);
    const TickType_t xFrequency = pdMS_TO_TICKS(samplingInterval);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while(true) {
        if (stateMachine->cm_pid){ 
            stateMachine->cm_pid->update();
            Serial.println("pid task is running");
        }
        else {
            Serial.println("pid pointer not allocated");
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
  } 

int StateMachine::go() {
    switch (this->currentState) {
        case CANDLE_STATES::STANDBY:
            //screen on,
            //poll user input or make it an interrupt,
            break;
        case CANDLE_STATES::HEATING:
            if (!cm_pid) {
                cm_pid = new PID(-127, 120, 55);
                cm_pid->Kp = 8.0f;
                cm_pid->Ki = 0.2f;
                cm_pid->Kd = 0.1f;
                cm_pid->tau = 0.05f;
                cm_pid->T = static_cast<float>(samplingInterval) / 1000.0f;
                Serial.printf("T = %.4f", cm_pid->T);
                //create task and pass pointer to state machine to be able to update PID within task
                xTaskCreate(pidTask, "update PID", 1024, this, 1, &pidTaskHandle);
            }
            break;
        case CANDLE_STATES::DISPENSING:
            //run dispensing motors
            break;
        case CANDLE_STATES::MIXING: 
            //run mixing motors and stuff
            break;
        case CANDLE_STATES::WICK_PLACEMENT:
            //move the wick placement stuff around idk
            break;
        case CANDLE_STATES::COOLING:
            //run the fan and stuff
            break;
        case CANDLE_STATES::EJECTING:
            break;
    }
    return 0;
}

void StateMachine::nextState() {
    switch (this->currentState) {
        case CANDLE_STATES::STANDBY:
        // clean up anything from standby, probably transition ui stuff
            break;
        case CANDLE_STATES::HEATING:
        // cleans up pid stuff in transition to next state
            if (pidTaskHandle != NULL) {
                vTaskSuspend(pidTaskHandle);
                pidTaskHandle = NULL;
            }
            if (cm_pid) {
                delete cm_pid;
                cm_pid = nullptr;
                Serial.println("deleted cm_pid in nextState");
            }
            break;
            // TODO: ASK SHREYAS IF THE HEATING SHOULD BE RUNNING WHILE DISPENSING IS HAPPENING

        case CANDLE_STATES::DISPENSING:
            break;

    }
    this->currentState = candleTransitions[this->currentState];
    Serial.print("next state is ");
    Serial.println(this->currentState);
}

void StateMachine::setState(CANDLE_STATES newState) {
    this->currentState = newState;
}