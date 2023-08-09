#ifndef SYSTEM_MAP
#define SYSTEM_MAP
#ifndef __clang__
#include <thread>
#include <iostream>
#include <chrono>
#endif
#include<stdlib.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_map>
#include "baseIP.cpp"
#include "guard.h"
// #include "slave_config.cpp"
// #include "master_config.cpp"
using namespace std;

#define GLOBAL_SYS_MAP_SIZE 10
#define CLEAR_AFTER_WRITE true
#define CLEAR_AFTER_READ true
#define CLEAR_AFTER_WRITE_DELAY 1
#define CLEAR_AFTER_READ_DELAY 1

class system_memory_map : public Log{
    public:
        static unordered_map<string,int> *global_memory_map;        
        int IP_ID;                                          //TODO: for future use
        int sys_map_size = GLOBAL_SYS_MAP_SIZE;
        int *valid = new int[sys_map_size];
        
        system_memory_map(){
            IP_ID = 0;
            for(int i = 0; i < sys_map_size; i++){
                valid[i] = 0;
            }
        }
    public:
        void display_valid_bits();
        bool check_valid_bit(int offset);
        void print_map(unordered_map<string, int> const &global_memory_map);
        void write_to_system_map(string reg, int value); 
        int read_system_map(string key);
        void update_system_reg_value(string key, int value);
};

unordered_map<string,int> *system_memory_map::global_memory_map = new unordered_map<string,int>();
void system_memory_map::display_valid_bits(){
                    // printf("Displaying valid bits: \n");
                    to_console("Valid bit values are: ",2);
                    for (int i = 0; i < sys_map_size; i++)
                    {
                        // printf("valid bit: %d", valid[i]);
                        to_console(to_string(valid[i]),2);
                    }
                }
bool system_memory_map::check_valid_bit(int offset){
    if(valid[offset]==1){
        // to_console("Valid bit is 1",2);
        return true;
    }
    else{
        // to_console("Valid bit is 0",2);
        return false;
    }
}

void system_memory_map::update_system_reg_value(string key, int value){
            int index_to_key_update;
            index_to_key_update = global_memory_map->size() - distance(global_memory_map->begin(), global_memory_map->find(key)) - 1;
            valid[index_to_key_update] = 1;
            auto it = global_memory_map->find(key);
            if(it != global_memory_map->end()){
                it->second = value;
            }
            else{
                string str = "system memory-mapped register " + key + " not found" + '\n';
                to_console(str,1);
            }
        }

int system_memory_map::read_system_map(string key){
            int index_to_key;
            auto iter = global_memory_map->find(key);
            if (iter == global_memory_map->end()){
                string str = "system memory-mapped register " + key + " not found" + '\n';
                to_console(str,1);
                return -1;
            }
            else
                index_to_key = global_memory_map->size() - distance(global_memory_map->begin(), global_memory_map->find(key)) - 1;
                if(valid[index_to_key]==1){
                    return iter->second;
                    #ifndef __clang__
                    cout<<"Value of register "<<iter->first<<" = "<<iter->second<<endl;
                    #endif
                    if(CLEAR_AFTER_READ){
                        valid[index_to_key] = 0;
                        string str = "valid[" + to_string(index_to_key) + "]" + " = 0" + " for register " + key;
                        to_console(str,2);
                    }
                }
                else{
                    string str = "system memory-mapped register " + key + " not valid, data stale";
                    to_console(str,1);
                    return -1;
                }
}

int valid_status = 0;
void system_memory_map::write_to_system_map(string reg, int value) {
    global_memory_map->insert(make_pair(reg, value));
    valid[valid_status] = 1;
    string str = "valid[" + to_string(valid_status) + "]" + " = 1" + " for register " + reg;
    to_console(str,2);
    valid_status++;
}

void system_memory_map::print_map(unordered_map<string, int> const &global_memory_map){
    to_console("system memory map: ",2);
    int valid_counter = 0;
    for (auto const &pair: global_memory_map) {
        #ifndef __clang__
        std::cout << "{" << pair.first << ": " << pair.second << "}" << " : valid bit: " << valid[valid_counter] << "\n";
        #endif
    }
}
#endif

// int main(){
//     system_memory_map* SYS_MAP = new system_memory_map();
//     SYS_MAP->write_to_system_map("checksum",10);
//     SYS_MAP->check_valid_bit(0);
//     return 0;
// }