#ifndef SW
#define SW
#include "SSEL_HEADER.h"

class SWCONTROLLER : public slaveIP{
     public:
        INTERFACES::interfaceRegisters swTimerInit;
        INTERFACES::interfaceRegisters swTimerEnd;
        INTERFACES::interfaceRegisters swTrigger;
        INTERFACES::interfaceRegisters swDelayTimer;
        INTERFACES::interfaceRegisters swChecksumCRC;
    
    public:
        SWCONTROLLER(){
            INTERFACES::interfaceRegisters swTimerInit   = (INTERFACES::interfaceRegisters){"swTimerInit","OUTPUT"};
            INTERFACES::interfaceRegisters swTimerEnd    = (INTERFACES::interfaceRegisters){"swTimerEnd","OUTPUT"};
            INTERFACES::interfaceRegisters swTrigger     = (INTERFACES::interfaceRegisters){"swTrigger","OUTPUT"};
            INTERFACES::interfaceRegisters swDelayTimer  = (INTERFACES::interfaceRegisters){"swDelayTimer","INPUT"};
            INTERFACES::interfaceRegisters swChecksumCRC = (INTERFACES::interfaceRegisters){"swChecksumCRC","INPUT"};
        }
    private:
        int checksum_;
    
    public:    
        // SWCONTROLLER(){
        //     commitToFactory({swTimerInit, swTimerEnd, swTrigger, swDelayTimer, swChecksumCRC});
        // }

    public:
        void initTimer();
        void triggerCRC();
        void fetchChecksum();
        void stopTimer();
        void validateChecksum();
};

///////////////////////////////////////////END OF SOFTWARE SPECIFICATION////////////////////////////////////////////

void SWCONTROLLER::initTimer(){
    writeToSelfInterfaceRegister(&swDelayTimer, 1);
}

void SWCONTROLLER::triggerCRC(){
    writeToSelfInterfaceRegister(&swTrigger, 1);
}

void SWCONTROLLER::fetchChecksum(){
    checksum_ = swChecksumCRC.value;
}

void SWCONTROLLER::stopTimer(){
    writeToSelfInterfaceRegister(&swTimerEnd, 1);
}

void SWCONTROLLER::validateChecksum(){
    if(swDelayTimer.value>=3){
        exit(0);
    }
    else {
        string str = "[SW] DELAY LIMIT MET!";
        display_to_console(str,2);
        if(checksum_ == 65535){
            string str = "[SW] CRC MATCH!";
            // display_to_console(str,2);
        }
        else {
            string str = "[SW] CRC MISMATCH!";
            // display_to_console(str,2);
            exit(0);
        }
    }
}
#endif

// int main()
// {   
//     SWCONTROLLER software;
//     return 0;
// }  