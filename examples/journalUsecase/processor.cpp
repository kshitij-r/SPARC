#ifndef SW
#define SW
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class SW : public slaveIP{

    public:     
        interfaceRegisters userInput    = {"userInput","INPUT"};
        interfaceRegisters inputSensor  = {"inputSensor","INPUT"};
        interfaceRegisters driveMotor   = {"driveMotor","OUTPUT"};
        interfaceRegisters monTemp      = {"monTemp","OUTPUT"};
        interfaceRegisters monRPM       = {"monRPM","OUTPUT"};
        interfaceRegisters monTempACK   = {"monTempACK","INPUT"};
        interfaceRegisters monRPMACK    = {"monRPMACK","INPUT"};
   
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