#ifndef SI
#define SI
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

INTERFACES* interface = new INTERFACES;

DC_SUPPLY* dcSupply_instance         = new DC_SUPPLY;
DC_MOTOR* motor_instance             = new DC_MOTOR;
SW_CONTROLLER* sw_instance           = new SW_CONTROLLER;
USER_INTERFACE* uint_interface       = new USER_INTERFACE;
TEMP_MONITOR* temp_monitor_instance  = new TEMP_MONITOR;
RPM_MONITOR* rpm_monitor_instance    = new RPM_MONITOR;

void dcPowerSupplyDriver(){
//atomic_init
    dcSupply_instance->supplyDCpower();
    uint_interface->dcPowerActive.value = 1;
    motor_instance->getDCsupply.value = 1;
//atomic_end
}

void dcMotorDriver(){
//atomic_init
    motor_instance->powerONDCmotor();
//atomic_end

//atomic_init
    motor_instance->spinmotor();
//atomic_end

//atomic_init
    motor_instance->stopmotor();
//atomic_end

//atomic_init
    while(motor_instance->motorRunning.value == 1){
        motor_instance->reportmotorRPM();
        rpm_monitor_instance->motorRPM.value = motor_instance->motorRPM.value;
    }
//atomic_end

//atomic_init
    while(motor_instance->motorRunning.value == 1){
        motor_instance->reportmotorTemp();
        temp_monitor_instance->motorTemp.value = motor_instance->motorTemp.value;
    }
//atomic_end
}

void swDriver(){
//atomic_init
    sw_instance->takeUserinput();
//atomic_end
}

void userInterfaceDriver(){

}

void tempMonitorDriver(){
//atomic_init
    temp_monitor_instance->getThresholdTemp();
//atomic_end

//atomic_init
    temp_monitor_instance->getMotorTemp();
//atomic_end

//atomic_init
    temp_monitor_instance->reportTempStatus();
//atomic_end
}

void rpmMonitorDriver(){
//atomic_init
    rpm_monitor_instance->getThresholdRPM();
//atomic_end

//atomic_init
    rpm_monitor_instance->getMotorRPM();
//atomic_end

//atomic_init
    rpm_monitor_instance->reportRPMStatus();
//atomic_end
}
#endif

int main(){
    thread worker1(dcPowerSupplyDriver);
    worker1.detach();
    thread worker2(dcMotorDriver);
    worker2.detach();
    thread worker3(swDriver);
    worker3.detach();
    thread worker4(userInterfaceDriver);
    worker4.detach();
    thread worker5(tempMonitorDriver);
    worker5.detach();
    thread worker6(rpmMonitorDriver);
    worker6.detach();
    return 0;
}