#ifndef USERINT
#define USERINT
#include "../../headers/SSEL_HEADER.h"

// using namespace std;

// class USER_INTERFACE : public slaveIP{

//     public:     
//         interfaceRegisters stateVaccuum      = {"motorRPM","INPUT"};
//         interfaceRegisters thresholdRPM  = {"thresholdRPM","INPUT"};
//         interfaceRegisters overSpeed     = {"overSpeed","OUTPUT"};
   
//     private:
        
//     public:
//         void getMotorRPM(const int& value);
//         void reportRPMStatus();
// }; 
// #endif

// void RPM_SENSOR::getMotorRPM(const int& value){
//     motorRPM_ = value;
//     motorRPM.value = motorRPM_;
// }

// void RPM_SENSOR::reportRPMStatus(){
//     if(motorRPM.value>thresholdRPM.value){
//         overSpeed.value = 1;
//     }
// }