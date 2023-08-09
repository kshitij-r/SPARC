#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include <queue>
#include <map>
#include "baseIP.cpp"
#include "memory_model.cpp"
#include "slave_config.cpp"
#include "master_config.cpp"
#include "crc_module.cpp"
#include "sys_map.cpp"

// Every function/entity is its own thread.
/*
User can insert soft rules as comments to check the correctness of the specification.
The SSEL backend can create and insert those rules as assertions and check for correctness.
Soft rules can be created by using the following template:
-----> Start by appending //-- to the line where you intend to insert the rule.
-----> Then, insert the rule by defining some characteristic of a variable that you
       want to log. Terminate the line using --// at the end.
-----> These variables may be declared as global variables if the scope of the assertion 
       goes beyond the function.
-----> An example assertion is provided below.
-----------> CRC Module state 1 is false until CRC has received data from DMA.
-----------> CRC_FIFO_VALID is 1 after CRC has received data from DMA, else it is 0.
-----------> We declare a global variable(crc_exec_state1) to store the state of CRC Module state 1,
             and initialize it to false.
-----------> When DMA sends the data and it is received by CRC, we set the value of crc_exec_state1 to true.
----> SSEL will insert the following assertion and verify it using KLEE:
-----------> assert((CRC_FIFO_VALID)?(crc_exec_state1 = true):(crc_exec_state1 = false));
*/

//-- bool crc_exec_state1 = false;  --//

//DMA Module
void dma_driver(){
    if(!dma_controller.check_busy_sts()){
        int *data = ram.read_from_memory(1,0,0,3);
        dma_controller.ingress_fifo_push(data,4);
        crc.ingress_fifo = dma_controller.ingress_fifo; //sets CRC_FIFO_VALID = 1 
        //-- bool crc_exec_state1 = true; --//
        thread worker3(crc_module);
        worker3.join();
    }
}

//Memory Module 
void ram_driver(){
    // This will instantiate a RAM_MODULE object and populate the memory.
    display.Info("Initializing memory module");
}

//CRC Module
void crc_module(){
    crc.checksum_calc();
    SYS_MAP.write_to_system_map("checksum",crc.checksum);
}