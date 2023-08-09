#ifndef MASTERIP
#define MASTERIP
#ifndef __clang__
#include <thread>
#include <iostream>
#include <chrono>
#endif
#include <string>
#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
#include "baseIP.cpp"
#include "memory_model.cpp"
#include "sys_map.cpp"
// #include "slave_config.cpp"
using namespace std;

class masterIP : public memory_model, public system_memory_map{
public:
        bool m_ip_rst;
public:
    masterIP(){
        m_ip_rst = true;
        m_sts_busy = false;
        m_memory_map.clear();
    }
    void system_lvl_rst(bool rst);
    void system_clk(bool clk);
    void set_busy_sts(bool sts);
    int *read_memory_val(int clk, int rst, int start, int offset = 0){
             return memory_model::send_data_from_mem(clk, rst, start, offset = 0);
        }

    void delete_memory_val(int clk, int rst, int offset, int base = 0){
        memory_model::delete_from_memory(clk, rst, offset, base = 0);
        }

    void write_memory_val(int clk, int rst, int offset, int value, int base = 0){
        memory_model::write_to_memory(clk, rst, offset, value, base = 0);
        }
    //TODO: Maybe implement a FIFO here??
};

void masterIP::system_lvl_rst(bool rst){
        if(rst == true){
            m_sys_rst = true;
            m_sts_busy = false;
            baseIP::to_console("System level reset is asserted",2);
            baseIP::to_console("System wide busy status is set to false",2);
            }
        else{
            m_sys_rst = false;
            baseIP::to_console("System level reset is deasserted",2);
            }
    }

void masterIP::set_busy_sts(bool sts){
            // float delay_time = time_delay(delay, unit);
            m_sts_busy = sts;
            string str = "Busy status set to " + to_string(sts) + '\n';
            baseIP::to_console(str,2);
        }

void masterIP::system_clk(bool clk){
        if(clk == true){
            m_sys_clk = true;
            baseIP::to_console("System clock asserted",2);
            }
        }
#endif

// int main(){
//     masterIP master1;
//     return 0;
// }