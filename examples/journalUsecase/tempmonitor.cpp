#ifndef TEMPMON
#define TEMPMON
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class TEMP_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorTemp      = {"motorTemp","INPUT"};
        interfaceRegisters thresholdTemp  = {"thresholdTemp","INPUT"};
        interfaceRegisters tempStatusReq  = {"tempStatusReq","INPUT"};
        interfaceRegisters tempStatus     = {"tempStatus","OUTPUT"};
    
    private:
        int motortemp_ = 0;
        int threshold_ = 0;
        int overheat_  = 0;

    public:
        void getThresholdTemp();
        void getMotorTemp();
        void reportTempStatus();
}; 
#endif

void TEMP_MONITOR::getThresholdTemp(){
    threshold_ = thresholdTemp.value;
}

void TEMP_MONITOR::getMotorTemp(){
    motortemp_ = motorTemp.value;
}

void TEMP_MONITOR::reportTempStatus(){
    if(tempStatusReq.value){
        if(motortemp_>threshold_){
            overheat_ = 1;
            tempStatus.value = 1;
        }
        else{
            overheat_ = 0;
            tempStatus.value = 0;
        }
    }
}