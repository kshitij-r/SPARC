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
        interfaceRegisters motorTemp      = {"motorTemp","OUTPUT"};
    private:
        int  motorSpeed_ = 0;
        int  motorTemp_ = 0;
        bool motorRunning_ = false;
        bool powerSupply_ = false;
    public:
        void powerONDCmotor();
        void spinmotor();
        void stopmotor();
        void reportmotorRPM();
        void reportmotorTemp();
}; 
#endif

void DC_MOTOR::powerONDCmotor(){
    if(getDCsupply.value == 1){
        powerSupply_ = true;
        cout << "Motor power on.."<<endl;
    }
}

void DC_MOTOR::spinmotor(){
    if((powerSupply_) && (startMotor.value == 1) && (stopMotor.value != 1)){
        motorRunning_ = true;
        motorRunning.value = 1;
        cout << "Motor running.."<<endl;
    }
    while((motorRunning_ == 1) && (stopMotor.value != 1)){
        motorSpeed_ = motorSpeed_ + 1;
        motorTemp_ = motorTemp_ + 2;
        motorTemp.value = motorTemp_;
        motorRPM.value = motorSpeed_;
        cout << "Motor running speed -  "<< motorRPM.value<<endl;
        cout << "Motor running temp -  "<< motorTemp.value<<endl;
        if(motorSpeed_ > 100){
            cout << "Motor overspeed -  "<< motorRPM.value<<" motor shutting off..."<<endl;
            break;
        }
        if(motorTemp_ > 200){
            cout << "Motor overheat -  "<< motorTemp.value<<" motor shutting off..."<<endl;
            break;
        }
    }
}

void DC_MOTOR::stopmotor(){
    if((stopMotor.value == 1) && (motorRunning_)){
        motorRunning_ = false;
        cout << "Motor stopping.."<<endl;
        motorSpeed_ = 0;
        while(motorTemp_>10){
            motorTemp_ = motorTemp_ - 10;
            // cout << "Motor stopping temp -  "<< motorTemp.value<<endl;
        }
        motorTemp.value = motorTemp_;
    }
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

// int main(){
//     DC_MOTOR* dc_motor_inst = new DC_MOTOR;

//     // Supply DC power
//     dc_motor_inst->getDCsupply.value = 1;
//     dc_motor_inst->powerONDCmotor();

//     // Spin DC motor
//     dc_motor_inst->startMotor.value = 1;
//     dc_motor_inst->spinmotor();

//     for(int i = 0;i<5;i++){}

//     // Stop DC motor
//     dc_motor_inst->stopMotor.value = 1;
//     dc_motor_inst->stopmotor();


//     return 0;
// }