#ifndef TEMPMON
#define TEMPMON
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class TEMP_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorTemp      = {"motorTemp","INPUT",0};
        interfaceRegisters thresholdTemp  = {"thresholdTemp","INPUT",0};
        interfaceRegisters tempStatus     = {"tempStatus","OUTPUT"};
    
    private:
        bool thresholdAcquired_ = false;
        bool tempAcquired_ = false;
        int motortemp_ = 0;
        int threshold_ = 0;
        bool overheat_  = false;

    public:
        void waitForThresholdTemp();
        void waitForMotorTemp();
        void checkTempStatus();
        void reportTempStatus();
}; 
#endif

void TEMP_MONITOR::waitForThresholdTemp(){
    while(true){
        if(thresholdTemp.value!=0){
            threshold_ = thresholdTemp.value;
            thresholdAcquired_ = true;
            break;
        }
    }
}

void TEMP_MONITOR::waitForMotorTemp(){
    while(true){
        if(motorTemp.value!=0){
            motortemp_ = motorTemp.value;
            tempAcquired_ = true;
            break;
        }
    }
}

void TEMP_MONITOR::checkTempStatus(){
    if(tempAcquired_ && thresholdAcquired_){
        if(motortemp_>threshold_){
            overheat_ = true;
        }
        else{
            overheat_ = false;
        }
    }
}

void TEMP_MONITOR::reportTempStatus(){
    // if(overheat_){
    //     tempStatus.value = 1;
    // }
    // else{
    //     tempStatus.value = 0;
    // }
}