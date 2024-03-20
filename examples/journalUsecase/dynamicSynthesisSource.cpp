#ifndef SI
#define SI
#include "../../../../headers/SPARC_JOURNAL.h"

using namespace std;

INTERFACES* interface = new INTERFACES;

DC_SUPPLY* dcSupply_instance         = new DC_SUPPLY;
DC_MOTOR* motor_instance             = new DC_MOTOR;
SW_CONTROLLER* sw_instance           = new SW_CONTROLLER;
USER_INPUT* input_instance           = new USER_INPUT;
USER_INTERFACE* uint_interface       = new USER_INTERFACE;
TEMP_MONITOR* temp_monitor_instance  = new TEMP_MONITOR;
RPM_MONITOR* rpm_monitor_instance    = new RPM_MONITOR;

//////////////////////////////////////////////////// User Input ////////////////////////////////////////////////////
void userInputDriver(){
//atomic_init    
    while(true){
        input_instance->commandToInterface();
        cout<<"vector generated is: "<<input_instance->inputToInterface.value<<endl;
    }
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// DC Power Supply ////////////////////////////////////////////////////
void dcPowerSupplyDriver(){
//atomic_init
    dcSupply_instance->supplyDCpowertoMotor();
    motor_instance->getDCsupply.value = 1;
//atomic_end

//atomic_init
    dcSupply_instance->supplyDCpowertoInterface();
    uint_interface->dcPowerActive.value = 1;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// User Interface ////////////////////////////////////////////////////
void userInterfaceDriver(){
//atomic_init
    uint_interface->waitOnDCPower();
//atomic_end

//atomic_init
    uint_interface->waitOnUserInput();
//atomic_end

//atomic_init
    uint_interface->sendInputtoSW();
    sw_instance->userInput.value = uint_interface->turnMotorON.value;
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// DC Motor ////////////////////////////////////////////////////
void dcMotorDriver(){
//atomic_init
    motor_instance->waitForDCSupply();
//atomic_end

//atomic_init
    motor_instance->waitForMotorCommand();
//atomic_end

//atomic_init
    motor_instance->stopMotor();
//atomic_end

//atomic_init
    motor_instance->spinMotor();
//atomic_end

//atomic_init
    motor_instance->reportmotorRPM();
    rpm_monitor_instance->motorRPM.value = motor_instance->motorRPM.value;
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
    sw_instance->takeUserinput();
//atomic_end

//atomic_init
    sw_instance->setRPMThreshold();
    rpm_monitor_instance->thresholdRPM.value = sw_instance->RPMthreshold.value;
//atomic_end

//atomic_init
    sw_instance->setTempThreshold();
    temp_monitor_instance->thresholdTemp.value = sw_instance->tempthreshold.value;
//atomic_end

//atomic_init
    sw_instance->startMotor();
    motor_instance->statusMotor.value = sw_instance->driveMotor.value;
//atomic_end

//atomic_init
    sw_instance->stopMotorRunning();
    motor_instance->statusMotor.value = sw_instance->driveMotor.value;
//atomic_end

//atomic_init
    sw_instance->checkRPMStatus();
//atomic_end

//atomic_init
    sw_instance->checkTempStatus();
//atomic_end
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// Temp Monitor ////////////////////////////////////////////////////
void tempMonitorDriver(){
//atomic_init
    temp_monitor_instance->waitForThresholdTemp();
//atomic_end

//atomic_init
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
    return 0;
}