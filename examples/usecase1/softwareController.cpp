#ifndef SW
#define SW
#include "../../headers/SSEL_HEADER.h"

class SOFTWARECONTROLLER : public slaveIP{
     public:
        interfaceRegisters initTimer = {"initTimer","OUTPUT"};
        interfaceRegisters timerDuration = {"initTimer","timerDuration"};
        interfaceRegisters initCRC = {"initCRC","OUTPUT"};
        interfaceRegisters resetReq = {"resetReq","OUTPUT"};
        interfaceRegisters swChecksum = {"swChecksum","INPUT"};
        interfaceRegisters timerEnd = {"timerEnd","INPUT"};
    
    private:
        int checksum_;
        bool resetAsserted_ = false;
    
    public:
        void startTimer();
        void triggerCRC();
        void validateChecksum();
        void waiton_Reset();
};

///////////////////////////////////////////END OF SOFTWARE SPECIFICATION////////////////////////////////////////////

void SOFTWARECONTROLLER::startTimer(){
    timerDuration.value = 5;
    initTimer.value = 1;
}

void SOFTWARECONTROLLER::triggerCRC(){
    initCRC.value = 1;
}

void SOFTWARECONTROLLER::validateChecksum(){
    if(swChecksum.value == 65535){
        string str = "[SW] CRC MATCH!";
        // display_to_console(str,2);
        resetReq.value = 1;    // make an event for this
    }
    else{
        string str = "[SW] CRC MISMATCH!";
        // display_to_console(str,0);
    }
}

void SOFTWARECONTROLLER::waiton_Reset(){
    while(true){
        if(m_ip_rst == false){
            // crc_trigger();
            resetAsserted_ = true;
            break;
        }
        break;
    }
    // cout<<"Reset Asserted"<<endl;
}

// bool SOFTWARECONTROLLER::monitor_rst(){
//     while(true){
//         if(m_ip_rst == false){
//             return true;
//             break;
//         }
//         else{
//             return false;
//         }
//     }
// }
#endif

// int main()
// {   
//     SOFTWARECONTROLLER software;
//     software.m_ip_rst = false;
//     software.waiton_Reset();
//     software.monitorTimer();
//     return 0;
// }  