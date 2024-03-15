#ifndef TEMPMON
#define TEMPMON
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class DC_MOTOR : public slaveIP{

    public:     
        interfaceRegisters motorTemp      = {"motorTemp","INPUT"};
        interfaceRegisters thresholdTemp  = {"thresholdTemp","INPUT"};
        interfaceRegisters overHeat       = {"overHeat","OUTPUT"};
    
    private:
        int motortemp_;

    public:
        void getMotorTemp(const int& value);
        void reportTempStatus();
}; 
#endif

void DC_MOTOR::getMotorTemp(const int& value){
    motortemp_ = value;
    motorTemp.value = motortemp_;
}

void DC_MOTOR::reportTempStatus(){
    if(motorTemp.value>thresholdTemp.value){
        overHeat.value = 1;
    }
}