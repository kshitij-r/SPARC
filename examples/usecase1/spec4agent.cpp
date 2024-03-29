#ifndef SYS
#define SYS
#include "../../../../headers/SPARC_HEADER.h"

RESET_CONTROLLER* reset_control = new RESET_CONTROLLER;
CRC_CONTROLLER* crc = new CRC_CONTROLLER;
TIMER_CONTROLLER* timer = new TIMER_CONTROLLER;
SOFTWARECONTROLLER* software = new SOFTWARECONTROLLER;

INTERFACES* interface = new INTERFACES;

bool __event__timerSet = false;
bool __event__timerfinish = false;
bool __event__resetRequest = false;

bool __assertion__globalresetAssert = false;
bool __assertion__crcTriggerAssert = false;
bool __assertion__timerTriggerassert = false;

void resetDriver(){
    //atomic_init
    reset_control->issueSysRST();
    //atomic_end

    //atomic_init
    wait__(__event__resetRequest);
    //atomic_end

    //atomic_init
    reset_control->issueGlbRST();
    //__assertion__globalresetAssert = true;
    //atomic_end
}

void swDriver(){
    //atomic_init
    software->waiton_Reset();
    //atomic_end

    //atomic_init
    timer->duration.value = 3;
    timer->startTimer.value = 1;
    
    __event__timerSet = true;
    //__assertion__timerTriggerassert = true;
    //atomic_end
    
    //atomic_init
    crc->crcTrigger.value = 1;
    //__assertion__crcTriggerAssert = true;
    //atomic_end

    //atomic_init
    if(!__event__timerfinish){
    software->swChecksum = crc->crcChecksum;
    software->validateChecksum();
    reset_control->req.value = 1;
    __event__resetRequest = true;
    //__assertion__crcTriggerAssert = true;
    }
    else{
        exit(0);
    }   
    //atomic_end
}

void crcDriver(){
    //atomic_init
    crc->waiton_Reset();
    //atomic_end

    //atomic_init
    crc->crc_trigger();
    //atomic_end

    //atomic_init
    crc->checksum_calc();
    //atomic_end
}

void timerDriver(){
    //atomic_init
    timer->waiton_Reset();
    //atomic_end

    //atomic_init
    wait__(__event__timerSet);
    //atomic_end

    //atomic_init
    timer->timer_start();
    //atomic_end

    //atomic_init
    wait__(timer->timerDone.value);
    //atomic_end

    //atomic_init
    software->timerEnd = timer->timerDone;
    __event__timerfinish = true;
    //atomic_end
}
#endif

int main(){
    thread worker1(resetDriver);
    worker1.detach();
    thread worker2(swDriver);
    worker2.detach();
    thread worker3(timerDriver);
    worker3.detach();
    thread worker4(crcDriver);
    worker4.detach();
    
    cout<<"CRC thread Complete"<<endl;
    cout<<"Timer thread Complete"<<endl;
    cout<<"SW thread Complete"<<endl;
    cout<<"Reset thread Complete"<<endl;
        //--assert(!__assertion__globalresetAssert || (__assertion__globalresetAssert && __event__resetRequest));
        //--assert(!__assertion__crcTriggerAssert || (__assertion__crcTriggerAssert && __assertion__timerTriggerassert));
        return 0;
}

