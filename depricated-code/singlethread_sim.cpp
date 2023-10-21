/*
--> Headers from concurrent source file
*/
#include "SYSTEM_HEADER.h"

#define SINGLE_ENTRY_POINT 1

using namespace std;

/*
--> Entity class object instantiation
*/
SWCONTROLLER* software = new SWCONTROLLER;
TIMER_MODULE* timer = new TIMER_MODULE;
CRC_MODULE* crc = new CRC_MODULE;
INTERFACES* interface = new INTERFACES;

/*
--> Specification Entity Blocks
*/

// --> timerDriver_process instance
void timerDriver_process(queue<int> queue_inst){
    if(queue_inst.size() == 0){
        return;
    }
    int instruction = queue_inst.front();
    switch(instruction){
        case 1:
                timer->init_timer();
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
                timer->end_timer();
                    software->swDelayTimer.value = interface->queryInterfaceRegisters(&timer->DELAY);
                queue_inst.pop();
    }
}

// --> crcDriver_process instance
void crcDriver_process(queue<int> queue_inst){
    if(queue_inst.size() == 0){
        return;
    }
    int instruction = queue_inst.front();
    switch(instruction){
        case 1:
                crc->crc_trigger();
                    software->swChecksumCRC.value = interface->queryInterfaceRegisters(&crc->crcChecksum);
                queue_inst.pop();
    }
}

// --> swDriver_process instance
void swDriver_process(queue<int> queue_inst){
    if(queue_inst.size() == 0){
        return;
    }
    int instruction = queue_inst.front();
    switch(instruction){
        case 1:
                interface->writeToExtInterfaceRegister(&timer->startTimer, 1);
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
                interface->writeToExtInterfaceRegister(&crc->crcTrigger, 1);
                    interface->writeToExtInterfaceRegister(&timer->stopTimer, 1);
                    software->fetchChecksum();
                    software->validateChecksum();
                queue_inst.pop();
    }
}

/*
--> Main test harness and Symbolic Test Function
*/
int main(){
    int process_ID;
    int iterator = 1;
    int common_initial_state = SINGLE_ENTRY_POINT;
    int timerDriver_initial_state;
    queue<int> timerDriver_queue;
    timerDriver_queue.push(common_initial_state);
    queue<int> crcDriver_queue;
    crcDriver_queue.push(common_initial_state);
    int swDriver_initial_state;
    queue<int> swDriver_queue;
    swDriver_queue.push(common_initial_state);
    timerDriver_process(timerDriver_queue);
    crcDriver_process(crcDriver_queue);
    swDriver_process(swDriver_queue);

/*
--> Symbolic execution test platform
*/
    while(iterator > 0){
        klee_make_symbolic(&process_ID, sizeof(process_ID), "process_ID");
        if(process_ID == 2){
            klee_make_symbolic(&timerDriver_initial_state, sizeof(timerDriver_initial_state), "timerDriver_initial_state");
            if(timerDriver_initial_state == 1){
                timerDriver_queue.push(timerDriver_initial_state);
                swDriver_process(timerDriver_queue);
             }
        }
        else if(process_ID == 4){
            klee_make_symbolic(&swDriver_initial_state, sizeof(swDriver_initial_state), "swDriver_initial_state");
            if(swDriver_initial_state == 1){
                swDriver_queue.push(swDriver_initial_state);
                swDriver_process(swDriver_queue);
             }
        }
    iterator--;
    }
/*
--> Assertions
*/
  return 0;
}