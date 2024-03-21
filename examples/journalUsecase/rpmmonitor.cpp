#ifndef RPMMON
#define RPMMON
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class RPM_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorRPM      = {"motorRPM","INPUT",0};
        interfaceRegisters thresholdRPM  = {"thresholdRPM","INPUT",0};
        interfaceRegisters RPMStatus     = {"RPMStatus","OUTPUT"};
    
    private:
        bool thresholdAcquired_ = false;
        bool RPMAcquired_ = false;
        int motorRPM_ = 0;
        int threshold_ = 0;
        bool overspeed_  = false;

    public:
        void waitForThresholdRPM();
        void waitForMotorRPM();
        void checkRPMStatus();
        void reportRPMStatus();
}; 
#endif

void RPM_MONITOR::waitForThresholdRPM(){
    while(true){
        if(thresholdRPM.value!=0){
            threshold_ = thresholdRPM.value;
            thresholdAcquired_ = true;
            break;
        }
    }
}

void RPM_MONITOR::waitForMotorRPM(){
    while(true){
        if(motorRPM.value!=0){
            motorRPM_ = motorRPM.value;
            RPMAcquired_ = true;
            break;
        }
    }
}

void RPM_MONITOR::checkRPMStatus(){
    if(RPMAcquired_ && thresholdAcquired_){
        if(motorRPM_>threshold_){
            overspeed_ = true;
        }
        else{
            overspeed_ = false;
        }
    }
}

void RPM_MONITOR::reportRPMStatus(){
    // if(overspeed_){
    //     RPMStatus.value = 1;
    // }
    // else{
    //     RPMStatus.value = 0;
    // }
}