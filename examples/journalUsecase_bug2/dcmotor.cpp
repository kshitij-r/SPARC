#ifndef DCMOTOR
#define DCMOTOR
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class DC_MOTOR : public slaveIP{

    public:     
        interfaceRegisters getDCsupply    = {"getDCsupply","INPUT"};
        interfaceRegisters statusMotor     = {"statusMotor","INPUT"};
        interfaceRegisters motorRunning   = {"motorRunning","OUTPUT"};
        interfaceRegisters motorRPM       = {"motorRPM","OUTPUT"};
        interfaceRegisters motorTemp      = {"motorTemp","OUTPUT"};
    private:
        int  motorSpeed_ = 0;
        int  motorTemp_ = 0;
        bool motorRunning_ = false;
        bool turnMotorOn_ = false;
        bool powerSupply_ = false;
    public:
        void waitForDCSupply();
        void waitForMotorCommand();
        void spinMotor();
        bool stopMotor();
        void reportmotorRPM();
        void reportmotorTemp();
}; 
#endif

void DC_MOTOR::waitForDCSupply(){
    while(true){
        if(getDCsupply.value == 1){
            powerSupply_ = true;
            break;
        }
    }
}

void DC_MOTOR::waitForMotorCommand(){
    if(powerSupply_){
        while(true){
            if(statusMotor.value == 1){
                turnMotorOn_ = true;
            }
            else if(statusMotor.value == 0){
                turnMotorOn_ = false;
            }
        }
    }
}

void DC_MOTOR::spinMotor(){
    if(turnMotorOn_){
        motorRunning_ = true;
        motorSpeed_ = motorSpeed_ + 5;
        motorTemp_ = motorTemp_ + 1;
    }
}

bool DC_MOTOR::stopMotor(){
    if(!turnMotorOn_){
        motorRunning_ = false;
        motorSpeed_ = 0;
        motorTemp_ = 0;
        return true;
    }
    return false;
}

void DC_MOTOR::reportmotorRPM(){
    if(motorRunning_){
        motorRPM.value = motorSpeed_;
    }
    else{
        motorRPM.value = 0;
    }
}

void DC_MOTOR::reportmotorTemp(){
    if(motorRunning_){
        motorTemp.value = motorTemp_;
    }
    else{
        motorTemp.value = 0;
    }
}