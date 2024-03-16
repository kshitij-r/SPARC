#ifndef RPMMON
#define RPMMON
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class RPM_MONITOR : public slaveIP{

    public:     
        interfaceRegisters motorRPM      = {"motorRPM","INPUT"};
        interfaceRegisters thresholdRPM  = {"thresholdRPM","INPUT"};
        interfaceRegisters RPMStatusReq  = {"RPMStatusReq","INPUT"};
        interfaceRegisters RPMStatus     = {"RPMStatus","OUTPUT"};
    
    private:
        int motorRPM_ = 0;
        int threshold_ = 0;
        int overspeed_  = 0;

    public:
        void getThresholdRPM();
        void getMotorRPM();
        void reportRPMStatus();
}; 
#endif

void RPM_MONITOR::getThresholdRPM(){
    threshold_ = thresholdRPM.value;
}

void RPM_MONITOR::getMotorRPM(){
    motorRPM_ = motorRPM.value;
}

void RPM_MONITOR::reportRPMStatus(){
    if(RPMStatusReq.value){
        if(motorRPM_>threshold_){
            overspeed_ = 1;
            RPMStatus.value = 1;
        }
        else{
            overspeed_ = 0;
            RPMStatus.value = 0;
        }
    }
}