#ifndef CRC
#define CRC
#include "SSEL_HEADER.h"

class CRC_CONTROLLER : public slaveIP{
    public:
        interfaceRegisters crcTrigger = {"crcTrigger","INPUT"};
        interfaceRegisters crcChecksum = {"crcChecksum","OUTPUT"};
   
    public:
        void crc_trigger();
        void checksum_calc();
        void waiton_Reset();
    
    private:
        bool resetAsserted_ = false;
        bool triggerAsserted_ = false;
};

///////////////////////////////////////////END OF CRC SPECIFICATION////////////////////////////////////////////

void CRC_CONTROLLER::checksum_calc(){
    if(triggerAsserted_){
        int us_checksum = 0;
        ingress_fifo.push(20000);
        ingress_fifo.push(20000);
        ingress_fifo.push(25535);
        while(ingress_fifo.size()!=0){
            us_checksum = us_checksum + ingress_fifo.front();
            ingress_fifo.pop();
        }
        crcChecksum.value = us_checksum;
        string str = "[CRC] CALCULATED CHECKSUM IS: INT -> " + to_string(us_checksum);
        //  display_to_console(str,2);
    }
    else{
        string str = "[CRC] CRC Trigger not asserted";
        //  display_to_console(str,2);
    }
}

void CRC_CONTROLLER::crc_trigger(){
    if((crcTrigger.value == 1) && (resetAsserted_ == true) && (m_sts_busy == false)){
        m_sts_busy = true; 
        triggerAsserted_ = true;
        // checksum_calc();
        crcTrigger.value = 0;
    }
    else{
        m_sts_busy = false;
        crcTrigger.value = 0;
    }
    // cout<<"Trigger asserted"<<endl;
}

void CRC_CONTROLLER::waiton_Reset(){
    while(true){
        if(m_ip_rst == false){
            // crc_trigger();
            resetAsserted_ = true;
            break;
        }
    }
    // cout<<"Reset Asserted"<<endl;
}
#endif

// int main(){
//     CRC_CONTROLLER crc;
//     crc.m_ip_rst = false;
//     crc.crcTrigger.value = 1;
//     crc.waiton_Reset();
//     crc.crc_trigger();
//     crc.checksum_calc();
// }

