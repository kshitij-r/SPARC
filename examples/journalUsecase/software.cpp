#ifndef SW
#define SW
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class SW_CONTROLLER : public slaveIP{
    
    public:     
        interfaceRegisters userInput      = {"userInput","INPUT"};
        interfaceRegisters driveMotor     = {"driveMotor","OUTPUT"};
        interfaceRegisters pauseMotor     = {"pauseMotor","OUTPUT"};
        interfaceRegisters RPMthreshold   = {"RPMthreshold","OUTPUT"};
        interfaceRegisters tempthreshold  = {"tempthreshold","OUTPUT"};
        interfaceRegisters monTempreq     = {"monTempreq","OUTPUT"};
        interfaceRegisters monRPMreq      = {"monRPMreq","OUTPUT"};
        interfaceRegisters monTempval     = {"monTempval","INPUT"};
        interfaceRegisters monRPMval      = {"monRPMval","INPUT"};
   
    private:
        int  motorRPM_ = 0;
        int  motorTemp_ = 0;
        bool userInputVal_ = false;  // (true->motor spin, false-> motor stop)
        bool motorRunning_ = false;
        int  RPMthreshold_ = 200;
        int  tempthreshold_ = 400;
    
    public:
        void takeUserinput();
        void setThreshold();
        void stopMotorRunning();
        void startMotor();
        void getMotorRPM();
        void getMotorTemp();
        void checkTempStatus();
        void checkRPMStatus();
}; 
#endif

void SW_CONTROLLER::takeUserinput(){
    if(userInput.value == 1){
        userInputVal_ = true;
    }
    else{
        userInputVal_ = false;
    }
}
void SW_CONTROLLER::setThreshold(){
    if(userInputVal_){
        RPMthreshold.value = RPMthreshold_;
        tempthreshold.value = tempthreshold_;
    }
}
void SW_CONTROLLER::startMotor(){
    if(userInputVal_){
        driveMotor.value = 1;
        motorRunning_ = true;
    }
}
void SW_CONTROLLER::stopMotorRunning(){
    if(userInputVal_){
        pauseMotor.value = 1;
        motorRunning_ = false;
    }
}
void SW_CONTROLLER::getMotorRPM(){
    while(motorRunning_){
        monRPMreq.value = 1;
        motorRPM_ = monRPMval.value;
    }
}
void SW_CONTROLLER::getMotorTemp(){
        monTempreq.value = 1;
        motorTemp_ = monTempval.value;
}

void SW_CONTROLLER::checkTempStatus(){
    if(motorTemp_>tempthreshold_){
        stopMotorRunning();
    }
}
void SW_CONTROLLER::checkRPMStatus(){
    if(motorRPM_>RPMthreshold_){
        stopMotorRunning();
    }
}

// int main(){
//     SW_CONTROLLER* sw_inst = new SW_CONTROLLER;

//     return 0;
// }
