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

    resetDriver_lock.lock();
    reset_control->issueSysRST();
    resetDriver_lock.unlock();


    resetDriver_lock.lock();
    while(!__event__resetRequest){};
    resetDriver_lock.unlock();


    resetDriver_lock.lock();
    reset_control->issueGlbRST();
    __assertion__globalresetAssert = true;
    resetDriver_lock.unlock();
}

void swDriver(){

    swDriver_lock.lock();
    software->waiton_Reset();
    swDriver_lock.unlock();


    swDriver_lock.lock();
    timer->duration.value = 3;
    timer->startTimer.value = 1;
    
    __event__timerSet = true;
    __assertion__timerTriggerassert = true;
    swDriver_lock.unlock();
    

    swDriver_lock.lock();
    crc->crcTrigger.value = 1;
    __assertion__crcTriggerAssert = true;
    swDriver_lock.unlock();


    swDriver_lock.lock();
    if(!__event__timerfinish){
    software->swChecksum = crc->crcChecksum;
    software->validateChecksum();
    reset_control->req.value = 1;
    __event__resetRequest = true;
    __assertion__crcTriggerAssert = true;
    }
    else{
        exit(0);
    }   
    swDriver_lock.unlock();
}

void crcDriver(){

    crcDriver_lock.lock();
    crc->waiton_Reset();
    crcDriver_lock.unlock();


    crcDriver_lock.lock();
    crc->crc_trigger();
    crcDriver_lock.unlock();


    crcDriver_lock.lock();
    crc->checksum_calc();
    crcDriver_lock.unlock();
}

void timerDriver(){

    timerDriver_lock.lock();
    timer->waiton_Reset();
    timerDriver_lock.unlock();


    timerDriver_lock.lock();
    while(!__event__timerSet){};
    timerDriver_lock.unlock();


    timerDriver_lock.lock();
    timer->timer_start();
    timerDriver_lock.unlock();


    timerDriver_lock.lock();
    while(!timer->timerDone.value){};
    timerDriver_lock.unlock();


    timerDriver_lock.lock();
    software->timerEnd = timer->timerDone;
    __event__timerfinish = true;
    timerDriver_lock.unlock();
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
        assert(!__assertion__globalresetAssert || (__assertion__globalresetAssert && __event__resetRequest));
        assert(!__assertion__crcTriggerAssert || (__assertion__crcTriggerAssert && __assertion__timerTriggerassert));
        return 0;
}

