#ifndef USERINT
#define USERINT
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;
class USER_INTERFACE : public slaveIP{

    public:     
        interfaceRegisters dcPowerActive = {"dcPowerActive","INPUT"};
        interfaceRegisters userInput     = {"userInput","INPUT"};
        interfaceRegisters turnMotorON   = {"turnMotorON","OUTPUT"};
    private:
        bool supplyActive_ = false;
        bool inputStatus_  = false;
        bool motorStatus_  = false;

    public:
        void waitOnDCPower();
        void waitOnUserInput();
        void sendInputtoSW();
}; 

void USER_INTERFACE::waitOnDCPower(){
    while(true){
        if(dcPowerActive.value == 1){
            supplyActive_ = true;
            // klee_print_range("Input ",userInput.value);
            // klee_print_range("Active ", supplyActive_);
            // klee_print_range("Motor status ", motorStatus_);
            break;
        }
    }
}

void USER_INTERFACE::waitOnUserInput(){
        if(supplyActive_){
            if(userInput.value == 1 && !motorStatus_){
                motorStatus_ = true;
                }
            else if(userInput.value == 0 && motorStatus_){
                motorStatus_ = false;
            }
        }
        // else{
        //     motorStatus_ = false;
        // }
    }
                // while(true){
                // if(supplyActive_){
                //     klee_print_range("yes ", supplyActive_);
                //     if(userInput.value == 1 && motorStatus_){
                //         goto CHECK_INPUT;
                //     }
                //     else if(userInput.value == 1 && !motorStatus_){
                //         motorStatus_ = true;
                //         sendInputtoSW();
                //         // break;
                //     }
                //     else if(userInput.value == 0 && motorStatus_){
                //         motorStatus_ = false;
                //         sendInputtoSW();
                //         // break;
                //     }
                //     else if(userInput.value == 0 && !motorStatus_){
                //         goto CHECK_INPUT;
                //     }
                // }
                // else{
                //     motorStatus_ = false;
                //     goto CHECK_INPUT;
                // }
                // }

void USER_INTERFACE::sendInputtoSW(){
    if(motorStatus_){
        turnMotorON.value = 1;
    }
    else{
        turnMotorON.value = 0;
    }
}
#endif

// int main(){
//     USER_INTERFACE uint_interface;
//     uint_interface.waitOnDCPower();
//     uint_interface.waitOnUserInput();
//     uint_interface.sendInputtoSW();

//     return 0;
// }