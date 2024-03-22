#ifndef SI
#define SI
#include "../../../../../headers/SPARC_JOURNAL.h"

using namespace std;

INTERFACES* interface = new INTERFACES;

DC_SUPPLY* dcSupply_instance         = new DC_SUPPLY;
DC_MOTOR* motor_instance             = new DC_MOTOR;
SW_CONTROLLER* sw_instance           = new SW_CONTROLLER;
USER_INPUT* input_instance           = new USER_INPUT;
USER_INTERFACE* uint_interface       = new USER_INTERFACE;
TEMP_MONITOR* temp_monitor_instance  = new TEMP_MONITOR;
RPM_MONITOR* rpm_monitor_instance    = new RPM_MONITOR;

bool __event__inputSentToInterface = false;
bool __event__DCPowerSentToInterface = false;
bool __event__DCPowerSentToMotor = false;
bool __event__inputSentINTtoSW = false;
bool __event__inputSentSWtoMotor = false;
bool __event__thresholdtoRPM = false;
bool __event__thresholdtoTemp = false;
bool __event__motorTemptoMON = false;
bool __event__motorRPMtoMON = false;

bool __assertion__motorstop = false;
bool __assertion__motoron = false;

//////////////////////////////////////////////////// User Input ////////////////////////////////////////////////////
void userInputDriver(){
//atomic_init    
    while(true){
        input_instance->commandToInterface();
        __event__inputSentToInterface = true;
        cout<<"[SPARC] input sent to interface"<<endl;
        break;
    }
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// DC Power Supply ////////////////////////////////////////////////////
void dcPowerSupplyDriver(){
//atomic_init
    dcSupply_instance->supplyDCpowertoMotor();
    motor_instance->getDCsupply.value = 1;
    cout<<"[SPARC] power sent to motor"<<endl;
    __event__DCPowerSentToMotor = true;
//atomic_end

//atomic_init
    dcSupply_instance->supplyDCpowertoInterface();
    uint_interface->dcPowerActive.value = 1;
    __event__DCPowerSentToInterface = true;
    cout<<"[SPARC] power sent to interface"<<endl;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// User Interface ////////////////////////////////////////////////////
void userInterfaceDriver(){
//atomic_init
    wait__(__event__DCPowerSentToInterface);
    uint_interface->waitOnDCPower();
//atomic_end

//atomic_init
    wait__(__event__inputSentToInterface);
    uint_interface->waitOnUserInput();
//atomic_end

//atomic_init
    uint_interface->sendInputtoSW();
    sw_instance->userInput.value = uint_interface->turnMotorON.value;
    __event__inputSentINTtoSW = true;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// DC Motor ////////////////////////////////////////////////////
void dcMotorDriver(){
//atomic_init
    wait__(__event__DCPowerSentToMotor);
    motor_instance->waitForDCSupply();
//atomic_end

//atomic_init
    wait__(__event__inputSentSWtoMotor);
    motor_instance->waitForMotorCommand();
//atomic_end

//atomic_init
    motor_instance->stopMotor();
//atomic_end

//atomic_init
    motor_instance->spinMotor();
    __assertion__motoron = true;
//atomic_end

//atomic_init
    motor_instance->reportmotorRPM();
    rpm_monitor_instance->motorRPM.value = motor_instance->motorRPM.value;
    __event__motorRPMtoMON = true;
//atomic_end

//atomic_init
    motor_instance->reportmotorTemp();
    temp_monitor_instance->motorTemp.value = motor_instance->motorTemp.value;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// Software ////////////////////////////////////////////////////
void swDriver(){
//atomic_init
    wait__(__event__inputSentINTtoSW);
    sw_instance->takeUserinput();
//atomic_end

//atomic_init
    sw_instance->setRPMThreshold();
    rpm_monitor_instance->thresholdRPM.value = sw_instance->RPMthreshold.value;
    __event__thresholdtoRPM = true;
//atomic_end

//atomic_init
    sw_instance->setTempThreshold();
    temp_monitor_instance->thresholdTemp.value = sw_instance->tempthreshold.value;
//atomic_end

//atomic_init
    sw_instance->startMotor();
    motor_instance->statusMotor.value = sw_instance->driveMotor.value;
    __event__inputSentSWtoMotor = true;
//atomic_end

//atomic_init
    bool status = sw_instance->stopMotorRunning();
    motor_instance->statusMotor.value = sw_instance->driveMotor.value;
    if(status){
        __assertion__motorstop = true;
    }
    else{
        __assertion__motorstop = false;
    }
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// Temp Monitor ////////////////////////////////////////////////////
void tempMonitorDriver(){
//atomic_init
    wait__(__event__thresholdtoTemp);
    temp_monitor_instance->waitForThresholdTemp();
//atomic_end

//atomic_init
    wait__(__event__motorTemptoMON);
    temp_monitor_instance->waitForMotorTemp();
//atomic_end

//atomic_init
    temp_monitor_instance->checkTempStatus();
//atomic_end

//atomic_init
    temp_monitor_instance->reportTempStatus();
    sw_instance->tempStatus.value = temp_monitor_instance->tempStatus.value;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// RPM Monitor ////////////////////////////////////////////////////
void rpmMonitorDriver(){
//atomic_init
    rpm_monitor_instance->waitForThresholdRPM();
//atomic_end

//atomic_init
    wait__(__event__motorRPMtoMON);
    rpm_monitor_instance->waitForMotorRPM();
//atomic_end

//atomic_init
    rpm_monitor_instance->checkRPMStatus();
//atomic_end

//atomic_init
    rpm_monitor_instance->reportRPMStatus();
    sw_instance->rpmStatus.value = rpm_monitor_instance->RPMStatus.value;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

int main(){
    thread worker1(dcPowerSupplyDriver);
    worker1.detach();
    thread worker2(dcMotorDriver);
    worker2.detach();
    thread worker3(swDriver);
    worker3.detach();
    thread worker4(userInputDriver);
    worker4.detach();
    thread worker5(userInterfaceDriver);
    worker5.detach();
    thread worker6(tempMonitorDriver);
    worker6.detach();
    thread worker7(rpmMonitorDriver);
    worker7.detach();
    //--assert(__assertion__motorstop);
    //--assert(__assertion__motoron);
    return 0;
}