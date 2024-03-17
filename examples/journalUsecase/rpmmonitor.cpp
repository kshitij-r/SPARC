#ifndef RPMMON
#define RPMMON
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class RPM_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorRPM      = {"motorRPM","INPUT"};
        interfaceRegisters thresholdRPM  = {"thresholdRPM","INPUT"};
        interfaceRegisters requestRPM    = {"requestRPM","INPUT"};
        interfaceRegisters overSpeed     = {"overSpeed","OUTPUT"};
   
    private:
        int motorRPM_;
        int thresholdRPM_;
    public:
        void getMotorRPM(const int& value);
        void getThresholdRPM(const int& value);
        void reportRPMStatus();
}; 
#endif

void RPM_MONITOR::getMotorRPM(const int& value){
    motorRPM_ = value;
    motorRPM.value = value;
}

void RPM_MONITOR::getThresholdRPM(const int& value){
    thresholdRPM_ = value;
    thresholdRPM.value = value;
}

void RPM_MONITOR::reportRPMStatus(){
    if (requestRPM.value == 1) {
        if(motorRPM.value>thresholdRPM.value)
            overSpeed.value = 1;
        else
            overSpeed.value = 0;
    }
}