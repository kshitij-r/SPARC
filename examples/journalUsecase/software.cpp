#ifndef SW
#define SW
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class SW_CONTROLLER : public slaveIP{
    
    public:     
        interfaceRegisters userInput      = {"userInput","INPUT"};    // 1 start, 0 stop
        interfaceRegisters RPMthreshold   = {"RPMthreshold","OUTPUT"};
        interfaceRegisters tempthreshold  = {"tempthreshold","OUTPUT"};
        interfaceRegisters driveMotor     = {"driveMotor","OUTPUT"};
        interfaceRegisters tempStatus     = {"tempStatus","INPUT"};
        interfaceRegisters rpmStatus      = {"rpmStatus","INPUT"};
   
    private:
        int  motorRPM_ = 0;
        int  motorTemp_ = 0;
        bool userInputVal_ = false;  // (true->motor spin, false-> motor stop)
        bool motorRunning_ = false;
        int  RPMthreshold_ = 200;
        int  tempthreshold_ = 400;
    
    public:
        void takeUserinput();
        void setRPMThreshold();
        void setTempThreshold();
        bool stopMotorRunning();
        void startMotor();
        void checkTempStatus();
        void checkRPMStatus();
}; 
#endif

void SW_CONTROLLER::takeUserinput(){
    while(true){
        if(userInput.value == 1){
            userInputVal_ = true;
            break;
        }
        else{
            userInputVal_ = false;
            break;
        }
    }
}

void SW_CONTROLLER::setRPMThreshold(){
    if(userInputVal_){
        RPMthreshold.value = RPMthreshold_;
    }
}

void SW_CONTROLLER::setTempThreshold(){
    if(userInputVal_){
        tempthreshold.value = tempthreshold_;
    }
}

void SW_CONTROLLER::startMotor(){
    if(userInputVal_){
        driveMotor.value = 1;
        motorRunning_ = true;
    }
}

bool SW_CONTROLLER::stopMotorRunning(){
    if(userInputVal_){
        driveMotor.value = 0;
        motorRunning_ = false;
        return true;
    }
    return false;
}

void SW_CONTROLLER::checkTempStatus(){
    if(tempStatus.value == 1){
        stopMotorRunning();
    }
}

void SW_CONTROLLER::checkRPMStatus(){
    if(rpmStatus.value == 1){
        stopMotorRunning();
    }
}