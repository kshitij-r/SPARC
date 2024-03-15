#ifndef RPMSEN
#define RPMSEN
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class RPM_SENSOR : public slaveIP{

    public:     
        interfaceRegisters motorRPM      = {"motorRPM","INPUT"};
        interfaceRegisters thresholdRPM  = {"thresholdRPM","INPUT"};
        interfaceRegisters overSpeed     = {"overSpeed","OUTPUT"};
   
    private:
        int motorRPM_;
    public:
        void getMotorRPM(const int& value);
        void reportRPMStatus();
}; 
#endif

void RPM_SENSOR::getMotorRPM(const int& value){
    motorRPM_ = value;
    motorRPM.value = motorRPM_;
}

void RPM_SENSOR::reportRPMStatus(){
    if(motorRPM.value>thresholdRPM.value){
        overSpeed.value = 1;
    }
}