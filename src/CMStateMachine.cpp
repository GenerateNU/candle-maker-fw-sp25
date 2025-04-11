#include "CMStateMachine.hpp"

//consts

//hash map
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
SemaphoreHandle_t errorMutex = xSemaphoreCreateMutex();

//tasks
void pidTask(void *parameter) {
    //we pass a reference to the state machine as parameter,
    // then cast it top the StateMachine class in here so we can access the pid in the scope of this task

    CMStateMachine* stateMachine = static_cast<CMStateMachine*>(parameter);

    //defines the amount of time in between updates in ticks instead of ms
    const TickType_t xFrequency = pdMS_TO_TICKS(samplingInterval);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while(true) {
        if (stateMachine->cm_pid){ 
            // takes the semaphore (which means we can safely perform update)
            if(xSemaphoreTake(errorMutex, portMAX_DELAY) == pdTRUE) {
                stateMachine->cm_pid->update(71.1f);
                int heatDutyCycle = static_cast<int>(stateMachine->cm_pid->out) + 127;
                ledcWrite(heatPwmChannel, heatDutyCycle);
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

// state machine constructor
CMStateMachine::CMStateMachine() : cm_pid(nullptr) {
    this->setState(CANDLE_STATES::STANDBY);    
}

int CMStateMachine::go() {
    switch (this->currentState) {
        case CANDLE_STATES::STANDBY: {
            //standby screen

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
            //screen on,
            //poll user input or make it an interrupt,
            
            // Shruz just told me the heating should turn on during standby and 
            if (!cm_pid) {
                cm_pid = new PID(-127, 128, 55);
                cm_pid->Kp = 8.0f;
                cm_pid->Ki = 0.2f;
                cm_pid->Kd = 0.1f;
                cm_pid->tau = 0.025f;
                cm_pid->limMaxInt = 50.0f;
                cm_pid->limMinInt = -50.0f;
                cm_pid->T = static_cast<float>(samplingInterval) / 1000.0f;
                Serial.printf("T = %.4f\n", cm_pid->T);

                //create task and pass pointer to state machine to be able to update PID within task
                xTaskCreate(pidTask, "update PID", 4096, this, 1, &pidTaskHandle);
            }
            break;
        }
        case CANDLE_STATES::HEATING: {

            //heating screen
            

            //Linked list to store previous error over 1 second
            std::list<float> errorList;
            for (int i = 0; i < samplingInterval*2; i++) {
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
                // the sum of the error terms needs to be less than 1.25 over 200 samples
                if (sum < 1.25f) {
                    Serial.printf("sum is %.3f\n", sum);
                    break;
                }
            }
            // wait 2 minutes for wax to melt completely
            delay(120000);
            break;
        }
        case CANDLE_STATES::DISPENSING:
            //dispensing screen    
        
            //run dispensing motors for certain amt of time/rotations
            break;
        case CANDLE_STATES::MIXING: 
            //mixing screen
        
            //run mixing motors and stuff for amt of time
            break;
        case CANDLE_STATES::WICK_PLACEMENT:
            //idk
        
            //move the wick placement stuff around idk
            break;
        case CANDLE_STATES::COOLING:
            //cooling screen
            
            //run the fan and stuff
            break;
        case CANDLE_STATES::EJECTING:
            //ejecting screen


            break;
    }
    return 0;
}

void CMStateMachine::nextState() {
    switch (this->currentState) {
        case CANDLE_STATES::STANDBY:
        // clean up anything from standby, probably transition ui stuff
            break;
        case CANDLE_STATES::HEATING:
            break;
        case CANDLE_STATES::DISPENSING:
            break;

    }
    this->currentState = candleTransitions[this->currentState];
    Serial.print("next state is ");
    Serial.println(this->currentState);
}

void CMStateMachine::setState(CANDLE_STATES newState) {
    this->currentState = newState;
}