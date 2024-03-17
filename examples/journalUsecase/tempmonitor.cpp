#ifndef TEMPMON
#define TEMPMON
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class TEMP_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorTemp      = {"motorTemp","INPUT"};
        interfaceRegisters thresholdTemp  = {"thresholdTemp","INPUT"};
        interfaceRegisters requestComp    = {"requestComp", "INPUT"};
        interfaceRegisters overHeat       = {"overHeat","OUTPUT"};
    
    private:
        int motortemp_;
        int thresholdTemp_;

    public:
        void getMotorTemp(const int& value);
        void getThresholdTemp(const int& value);
        void reportTempStatus();
}; 
#endif

void TEMP_MONITOR::getMotorTemp(const int& value){
    motortemp_ = value;
    motorTemp.value = motortemp_;

void TEMP_MONITOR::getThresholdTemp(const int& temp) {
    thresholdTemp_ = temp;
    thresholdTemp.value = thresholdTemp_;
}

void TEMP_MONITOR::reportTempStatus(){
    if (requestComp.value == 1) {
        if(motorTemp.value>thresholdTemp.value)
            overHeat.value = 1;
        else
            overHeat.value = 0;
    }
}