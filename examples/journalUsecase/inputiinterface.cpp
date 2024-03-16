#ifndef USERINT
#define USERINT
#include "../../headers/SSEL_HEADER.h"

using namespace std;
class USER_INTERFACE : public slaveIP{

    public:     
        interfaceRegisters dcPowerActive = {"dcPowerActive","INPUT"};
        interfaceRegisters turnMotorON = {"turnMotorON","OUTPUT"};
    private:
        bool supplyActive_ = false;
        bool motorStatus = false;

    public:
        void dcPowerON();
        void userInput();
        void sendInputtoSW();
}; 

void USER_INTERFACE::dcPowerON(){
    if(dcPowerActive.value == 1){
        supplyActive_ = true;
    }
}

void USER_INTERFACE::userInput(){
    if(supplyActive_ && turnMotorON.value){
        motorStatus = true;
    }
    else if(supplyActive_ && !turnMotorON.value){
        motorStatus = false;
    }
    else if(!supplyActive_){
        motorStatus = false;
    }
}

void USER_INTERFACE::sendInputtoSW(){
    if(motorStatus){
        turnMotorON.value = 1;
    }
    else{
        turnMotorON.value = 0;
    }
}
#endif