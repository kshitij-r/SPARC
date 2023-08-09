#ifndef CRC
#define CRC
#ifndef __clang__
#include <thread>
#include <iostream>
#endif
#include <string>
#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
#include <klee/klee.h>
#include "baseIP.cpp"
#include "sys_map.cpp"
#include "memory_model.cpp"
#include "slave_config.cpp"

class CRC_MODULE : public slaveIP{

    public:
        bool m_ip_rst;
        bool ingress_fifo_req = true;
        int checksum;
        queue <int> ingress_fifo;
        bool m_sts_busy;
        map<string,int> m_memory_map;
    
    public:
        CRC_MODULE(){
            m_ip_rst = true;
            m_sts_busy = false;
            m_memory_map.clear();
            queue <int> ingress_fifo;
            int checksum = 101;
        }
    
    public:
        bool crc_trigger(int trigger_case);
        void checksum_calc();
};

void CRC_MODULE::checksum_calc(){
            while(ingress_fifo.size()!=0){
                // printf("values are: %d\n",ingress_fifo.front());
                checksum = checksum + ingress_fifo.front();
                ingress_fifo.pop();
            }
}

bool CRC_MODULE::crc_trigger(int trigger){
    if(trigger == 0){
            checksum_calc();
            return true;
        }
        else{
            m_sts_busy = false;
            m_memory_map.clear();
            return false;
        }
}
#endif

// int main(){
//     CRC_MODULE crc_module;
//     crc_module.crc_trigger(0);
//     return 0;
// }