/*
--> Headers from concurrent source file
*/
#include "SYSTEM_HEADER.h"

#define SINGLE_ENTRY_POINT 1

using namespace std;

/*
--> Entity class object instantiation
*/
RESET_CONTROLLER* reset_control = new RESET_CONTROLLER;
CRC_CONTROLLER* crc = new CRC_CONTROLLER;
TIMER_CONTROLLER* timer = new TIMER_CONTROLLER;
SOFTWARECONTROLLER* software = new SOFTWARECONTROLLER;
INTERFACES* interface = new INTERFACES;

/*
--> Auto generated events
*/
bool __event__timerSet = false;
bool __event__timerfinish = false;
bool __event__resetRequest = false;
/*
--> Auto generated assertion variables
*/
bool __assertion__globalresetAssert = false;
bool __assertion__crcTriggerAssert = false;
bool __assertion__timerTriggerassert = false;

/*
--> Specification Entity Blocks
*/

// --> resetDriver_process instance
void resetDriver_process(queue<int> queue_inst){
    if(queue_inst.size() == 0){
        return;
    }
    int instruction = queue_inst.front();
    switch(instruction){
        case 1:
                reset_control->issueSysRST();
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
            if(__event__resetRequest){
                queue_inst.pop();
                queue_inst.push(3);
            }
            else{
                // return back to existing instruction {case: 2}
            }
        case 3:
                reset_control->issueGlbRST();
                    __assertion__globalresetAssert = true;
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
                software->waiton_Reset();
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
                timer->duration.value = 3;
                    timer->startTimer.value = 1;
                    __event__timerSet = true;
                    __assertion__timerTriggerassert = true;
                queue_inst.pop();
                queue_inst.push(3);
        case 3:
                crc->crcTrigger.value = 1;
                    __assertion__crcTriggerAssert = true;
                queue_inst.pop();
                queue_inst.push(4);
        case 4:
                while(!__event__timerfinish){
                    software->swChecksum = crc->crcChecksum;
                    software->validateChecksum();
                    reset_control->req.value = 1;
                    __event__resetRequest = true;
                    __assertion__crcTriggerAssert = true;
                    }
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
                crc->waiton_Reset();
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
                crc->crc_trigger();
                queue_inst.pop();
                queue_inst.push(3);
        case 3:
                crc->checksum_calc();
                queue_inst.pop();
    }
}

// --> timerDriver_process instance
void timerDriver_process(queue<int> queue_inst){
    if(queue_inst.size() == 0){
        return;
    }
    int instruction = queue_inst.front();
    switch(instruction){
        case 1:
                timer->waiton_Reset();
                queue_inst.pop();
                queue_inst.push(2);
        case 2:
            if(__event__timerSet){
                queue_inst.pop();
                queue_inst.push(3);
            }
            else{
                // return back to existing instruction {case: 2}
            }
        case 3:
                timer->timer_start();
                queue_inst.pop();
                queue_inst.push(4);
        case 4:
            if(timer->timerDone.value){
                queue_inst.pop();
                queue_inst.push(5);
            }
            else{
                // return back to existing instruction {case: 4}
            }
        case 5:
                software->timerEnd = timer->timerDone;
                    __event__timerfinish = true;
                queue_inst.pop();
    }
}

/*
--> Main test harness and Symbolic Test Function
*/
int main(){
    int process_ID;
    int common_initial_state = SINGLE_ENTRY_POINT;
    int resetDriver_initial_state;
    queue<int> resetDriver_queue;
    resetDriver_queue.push(common_initial_state);
    int swDriver_initial_state;
    queue<int> swDriver_queue;
    swDriver_queue.push(common_initial_state);
    int crcDriver_initial_state;
    queue<int> crcDriver_queue;
    crcDriver_queue.push(common_initial_state);
    int timerDriver_initial_state;
    queue<int> timerDriver_queue;
    timerDriver_queue.push(common_initial_state);
    resetDriver_process(resetDriver_queue);
    swDriver_process(swDriver_queue);
    crcDriver_process(crcDriver_queue);
    timerDriver_process(timerDriver_queue);

/*
--> Symbolic execution test platform
*/
    int schedular_queue_size;
    int rand_processID;
    klee_make_symbolic(&schedular_queue_size, sizeof(schedular_queue_size), "schedular_queue_size");
    klee_assume((schedular_queue_size>=4) & (schedular_queue_size<6));
    queue<int> scheduler_queue;
    for(int i = 0; i<schedular_queue_size; i++){
        klee_make_symbolic(&rand_processID, sizeof(rand_processID), "rand_processID");
        klee_assume(rand_processID<3 & rand_processID>0);
        scheduler_queue.push(rand_processID);
    }

    while(!scheduler_queue.empty()){
        process_ID = scheduler_queue.front();
        scheduler_queue.pop();
        if(process_ID == 1){
            klee_make_symbolic(&resetDriver_initial_state, sizeof(resetDriver_initial_state), "resetDriver_initial_state");
            if(resetDriver_initial_state == 1){
                resetDriver_queue.push(resetDriver_initial_state);
                resetDriver_process(resetDriver_queue);
             }
        }
        else if(process_ID == 2){
            klee_make_symbolic(&swDriver_initial_state, sizeof(swDriver_initial_state), "swDriver_initial_state");
            if(swDriver_initial_state == 1){
                swDriver_queue.push(swDriver_initial_state);
                swDriver_process(swDriver_queue);
             }
        }
        else if(process_ID == 3){
            klee_make_symbolic(&crcDriver_initial_state, sizeof(crcDriver_initial_state), "crcDriver_initial_state");
            if(crcDriver_initial_state == 1){
                crcDriver_queue.push(crcDriver_initial_state);
                crcDriver_process(crcDriver_queue);
             }
        }
        else if(process_ID == 4){
            klee_make_symbolic(&timerDriver_initial_state, sizeof(timerDriver_initial_state), "timerDriver_initial_state");
            if(timerDriver_initial_state == 1){
                timerDriver_queue.push(timerDriver_initial_state);
                timerDriver_process(timerDriver_queue);
             }
        }
    }
/*
--> Assertions
*/
 assert(!__assertion__globalresetAssert || (__assertion__globalresetAssert && __event__resetRequest));
 assert(!__assertion__crcTriggerAssert || (__assertion__crcTriggerAssert && __assertion__timerTriggerassert));
 assert(!__assertion__crcTriggerAssert || (__assertion__crcTriggerAssert && !__assertion__timerTriggerassert));
  return 0;
}