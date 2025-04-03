#include "CMStateMachine.hpp"

//consts
std::map<CANDLE_STATES,CANDLE_STATES> candleTransitions = {
    {CANDLE_STATES::STANDBY, CANDLE_STATES::HEATING},
    {CANDLE_STATES::HEATING, CANDLE_STATES::DISPENSING},
    {CANDLE_STATES::DISPENSING, CANDLE_STATES::MIXING},
    {CANDLE_STATES::MIXING, CANDLE_STATES::WICK_PLACEMENT},
    {CANDLE_STATES::WICK_PLACEMENT, CANDLE_STATES::COOLING},
    {CANDLE_STATES::COOLING, CANDLE_STATES::EJECTING},
    {CANDLE_STATES::EJECTING, CANDLE_STATES::STANDBY}
    };

//mutex (mutual exclusion) to allow the state machine to access the pid stuff while the pid task is running
SemaphoreHandle_t errorMutex;

//tasks
void pidTask(void *parameter) {
    //we pass a reference to the state machine as parameter,
    // then cast it top the StateMachine class in here so we can access the pid in the scope of this task

    StateMachine* stateMachine = static_cast<StateMachine*>(parameter);

    //defines the amount of time in between updates in ticks instead of ms
    const TickType_t xFrequency = pdMS_TO_TICKS(samplingInterval);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while(true) {
        if (stateMachine->cm_pid){ 
            // takes the semaphore (which means we can safely perform update)
            if(xSemaphoreTake(errorMutex, portMAX_DELAY) == pdTRUE) {
                stateMachine->cm_pid->update();
                xSemaphoreGive(errorMutex);
            }
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
        case CANDLE_STATES::STANDBY: {
            // cleans up pid stuff when intializing standby state
            if (pidTaskHandle != NULL) {
                vTaskSuspend(pidTaskHandle);
                pidTaskHandle = NULL;
            }
            if (cm_pid) {
                delete cm_pid;
                cm_pid = nullptr;
                Serial.println("deleted cm_pid in standby");
            }
            break;
            //screen on,
            //poll user input or make it an interrupt,
            
            // Shruz just told me the heating should turn on during standby and 
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
        }
        case CANDLE_STATES::HEATING: {
            //Linked list to store previous error
            std::list<float> errorList;
            for (int i = 0; i < 10; i++) {
                errorList.push_back(500.0f);
            }
            
            // the heating state will not be exited until the cumulative error over 10 samples is less than 1.25 degrees C
            while(true) {
                errorList.pop_back();
                // mutex statement to ensure error is accessed safely
                if (xSemaphoreTake(errorMutex, portMAX_DELAY) == pdTRUE) {
                    errorList.push_front(this->cm_pid->get_error());
                    xSemaphoreGive(errorMutex);
                }

                float sum = 0.0f;
                for (float errorVal : errorList) {
                    sum += errorVal;
                }
                // the sum of the error terms needs to be less than 2.5 over 10 samples
                if (sum < 1.25f) {
                    break;
                }
            }
        
            break;
        }
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
        
            // TODO: ASK SHREYAS IF THE HEATING SHOULD BE RUNNING WHILE DISPENSING IS HAPPENING
            break;
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