#ifndef SLAVEIP
#define SLAVEIP
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
#include "guard.h"
#include "baseIP.cpp"
#include "memory_model.cpp"
#include "sys_map.cpp"
// #include "master_config.cpp"
using namespace std;

class slaveIP : public memory_model, public system_memory_map{

    friend class core;
    public:
        static bool m_ip_rst;
        bool FIFO_VALID = false;
        bool ingress_fifo_req = true;
        queue <int> ingress_fifo;
        struct  interfaceRegisters{
                string name;
                string direction;
                int value;
                // bool commitLocalMap;
                // array<int, PATHSOURCESIZE> pathSource;
            };

    public:
        slaveIP(){
            m_ip_rst = true;
            m_sts_busy = false;
            m_memory_map.clear();
            while(ingress_fifo.size()!=0){
                ingress_fifo.pop();
            }
        }
        
        void reset_ip_instance();
        void set_busy_sts(bool sts);
        bool check_busy_sts();
        void ingress_fifo_push(int *value, int offset);
        int  ingress_fifo_pop(int offset);
        void display_fifo();
        void read_system_map(string reg){
            system_memory_map::read_system_map(reg);
        }
        void write_to_system_map(string reg, int value){
            system_memory_map::write_to_system_map(reg, value);
        }
        void print_memory_val(){
            memory_model::print_memory_val();
        }
        int *read_memory_val(int clk, int rst, int start, int offset = 0){
            return memory_model::send_data_from_mem(clk, rst, start, offset = 0);
        }
        void delete_memory_val(int clk, int rst, int offset, int base = 0){
            memory_model::delete_from_memory(clk, rst, offset, base = 0);
        }
        void write_memory_val(int clk, int rst, int offset, int value, int base = 0){
            memory_model::write_to_memory(clk, rst, offset, value, base = 0);
        }
};

bool slaveIP::m_ip_rst;

void slaveIP::reset_ip_instance(){
    m_sts_busy = false;
    m_memory_map.clear();
    while(ingress_fifo.size()!=0){
        ingress_fifo.pop();
    }
}

bool slaveIP::check_busy_sts(){
            if(m_sts_busy){
                string str = "IP is busy";
                display_to_console(str,2);
                return true;
            }
            else{
                string str = "IP is not busy";
                display_to_console(str,2);
                return false;
            }
        }

void slaveIP::set_busy_sts(bool sts){
                // float delay_time = time_delay(delay, unit);
                m_sts_busy = sts;
                string str = "Busy status set to " + to_string(sts) + '\n';
                display_to_console(str,2);
        }

int slaveIP::ingress_fifo_pop(int offset){
                int value;
                if(ingress_fifo_req && (ingress_fifo.size()!=0)){
                    while(offset>0){
                        value = ingress_fifo.front();
                        ingress_fifo.pop();
                        offset--;
                        display_to_console("Data popped from Ingress FIFO "+to_string(value),2);
                    }
                    return value;
                }
                else{
                    display_to_console("Ingress FIFO is not implemented in IP instance or FIFO empty",0);
                    exit(EXIT_FAILURE);
                    return -1;
                }
        }

void slaveIP::ingress_fifo_push(int *value, int offset){    
        if(ingress_fifo_req){
            for(int i=0;i<offset;i++){
                ingress_fifo.push(*(value+i));
            }
            FIFO_VALID = true;
        }
        else{
            display_to_console("Ingress FIFO is not implemented in IP instance",1);
            exit(EXIT_FAILURE);
        }
}

void slaveIP::display_fifo(){
    // string str = "Ingress FIFO contents: ";
    // printf("FIFO size: %d\n",ingress_fifo.size());
    if(ingress_fifo.size()!=0){
        // str += to_string(ingress_fifo.front()) + " ";
        printf("fifo contents: %d\n", ingress_fifo.front());
        ingress_fifo.pop();
    }
    else{
        // str += "Empty";
        printf("FIFO empty\n");
    }
}
#endif

// int main(){
//     slaveIP slave1;
//     return 0;
// }