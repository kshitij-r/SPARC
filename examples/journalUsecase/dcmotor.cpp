#ifndef DCMOTOR
#define DCMOTOR
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class DC_MOTOR : public slaveIP{

    public:     
        interfaceRegisters getDCsupply    = {"getDCsupply","INPUT"};
        interfaceRegisters startMotor     = {"startMotor","INPUT"};
        interfaceRegisters stopMotor      = {"stopMotor","INPUT"};
        interfaceRegisters motorRunning   = {"motorRunning","OUTPUT"};
        interfaceRegisters motorRPM       = {"motorRPM","OUTPUT"};
    private:
        int motorSpeed_ = 0;
        bool motorOn_ = false;
    public:
        void powerONDCmotor(const int& value);
        void spinmotor();
        void stopmotor();
        void reportmotorRPM();
}; 
#endif

void DC_MOTOR::powerONDCmotor(const int& value){
    if(value == 1) {
        motorRunning.value = 0;
        motorSpeed_ = 0;
        motorOn_ = true;
    }   

}
void DC_MOTOR::spinmotor(){
    if((motorOn_) && (startMotor.value == 1)){
        motorRunning.value = 1;
    }
    while(motorRunning.value == 1){
        motorSpeed_++;
        motorRPM.value = motorSpeed_;
        if(motorSpeed_++ > 2000){
            break;
        }
    }

}

void DC_MOTOR::stopmotor(){
    if((motorRunning.value == 1) && (stopMotor.value == 1) && (motorOn_)){
        motorOn_ = false;
        motorRunning.value = 0;
        motorSpeed_ = 0;
    }
    else{}
}

void DC_MOTOR::reportmotorRPM(){
    if(motorRunning.value == 1){
        motorRPM.value = motorSpeed_;
    }
    else{}
}