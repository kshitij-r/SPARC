#ifndef __clang__
#include <iostream>
#include <chrono>
#include <thread>
#endif
#include <string>
#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
#include "guard.h"
#include "baseIP.cpp"
#include "memory_model.cpp"
#include "slave_config.cpp"
#include "master_config.cpp"
#include "crc_module.cpp"
#include "sys_map.cpp"

system_memory_map* SYS_MAP = new system_memory_map;
CRC_MODULE* crc = new CRC_MODULE;
slaveIP* dma_controller = new slaveIP;
masterIP* reset_controller = new masterIP;
memory_model* ram = new memory_model;
masterIP* boot_controller = new masterIP;

void reset_ctl(){
    //atomic_init
    bool rst = true;
    if(rst){
        reset_controller->system_lvl_rst(true);
        reset_controller->system_clk(true);
    }
    //atomic_end
}

void ram_driver(){
    //atomic_init
    int *data = ram->send_data_from_mem(1,0,0,3);
    dma_controller->ingress_fifo_push(data,4);
    //atomic_end
}

void crc_module(){
    //atomic_init
    crc->checksum_calc();
    //atomic_end
    //atomic_init
    SYS_MAP->write_to_system_map("checksum",crc->checksum);
    //atomic_end
}

void dma_driver(){
    //atomic_init
    if(dma_controller->check_busy_sts()){
        crc->ingress_fifo = dma_controller->ingress_fifo; 
        thread worker3(crc_module);
        worker3.join();
    }
    //atomic_end
}

void boot_init(){
    //atomic_init
    while(dma_controller->check_busy_sts()){}
    //atomic_end
    //atomic_init
    thread worker2(dma_driver); 
    dma_controller->set_busy_sts(true);
    worker2.join();
    dma_controller->set_busy_sts(false);
    //atomic_end
    //atomic_init
    if(SYS_MAP->read_system_map("checksum") == crc->checksum){
         //-- assert(crc->checksum == SYS_MAP->read_system_map("checksum"));
        reset_controller->system_lvl_rst(true);
    }
    else{
        string str = "CRC checksum mismatch, opening debug access";
    }
    //atomic_end
}

int main(){
    thread worker(reset_ctl);
    worker.join();
    thread worker1(ram_driver);
    worker1.join();
    thread worker4(boot_init);
    worker4.join();
    return 0;
}