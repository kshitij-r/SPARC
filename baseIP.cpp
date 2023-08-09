#ifndef BASEIP
#define BASEIP
#ifndef __clang__
#include <thread>
#include <iostream>
#endif
#include "guard.h"
#include <klee/klee.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <map>
#include <unordered_map>
using namespace std;

class Log{
    // Logging class for debugging and status checks
    public:
        int loglevel;
        const int LoglevelError = 0;
        const int LoglevelWarning = 1;
        const int LoglevelInfo = 2; 
    private:
        int m_loglevel = LoglevelInfo;
    public:
        void Setlevel(int level);
        void to_console(const string message, int loglevel);     // Display warning message
};

// class baseIP{
class baseIP :  public Log{
    // Base class for all IP classes, master, slave, processor, and software classes are derived from this class
    public:
        map<string,int> m_memory_map;
        static bool m_sys_rst, m_sys_clk;
        bool m_sts_busy;
        // bool req_sts, ack_sts;
    private:
        map<string,int> m_status_ctl_reg;
    public:    
        baseIP(){
            m_sts_busy = false;
            // req_sts = false;
            // ack_sts = false;
            m_memory_map.clear();
            m_status_ctl_reg.clear();
        }
        void read_from_mem(string key);                        
        auto modify_reg_value(string key, int value);
        void print_map(map<string, int> const &m);
        // float time_delay(int delay, string unit);
        void set_busy_sts( bool sts);
};

bool baseIP::m_sys_rst = 0;
bool baseIP::m_sys_clk = 0;

void Log::Setlevel(int level){
        m_loglevel = level;
    }

void Log::to_console(const string message, int loglevel){
   display_to_console(message, loglevel);
   }

void baseIP::set_busy_sts(bool sts){
            // float delay_time = time_delay(delay, unit);
            m_sts_busy = sts;
            string str = "Busy status set to " + to_string(sts) + '\n';
            to_console(str,2);
        }

// float baseIP::time_delay(int delay, string unit){
//             auto start = chrono::high_resolution_clock::now();
//             if(unit == "seconds"){
//                 std::this_thread::sleep_for(std::chrono::seconds (delay));}
//             else if(unit == "milliseconds"){
//                 std::this_thread::sleep_for(std::chrono::milliseconds (delay));}
//             else if(unit == "nanoseconds"){
//                 std::this_thread::sleep_for(std::chrono::nanoseconds(delay));}
//             auto end = chrono::high_resolution_clock::now();
//             chrono::duration<float> duration = end - start;
//             return duration.count();
//         }

void baseIP::read_from_mem(string key){
            auto iter = m_memory_map.find(key);
            if (iter == m_memory_map.end()){
                string str = "memory-mapped register " + key + "not found" + '\n';
                to_console(str,0);
            }
            #ifndef __clang__
            cout<<"Value of register "<<iter->first<<" = "<<iter->second<<endl;
            #endif
        }

auto baseIP::modify_reg_value(string key, int value){
            auto iter = m_memory_map.find(key);
            if (iter == m_memory_map.end()){
                #ifndef __clang__
                cout<<"Memory mapped register " << key << "to be modified not found!!"<<endl;
                #endif            
            }
            else{
                iter->second = value;
            }
            return iter;
        }

void baseIP::print_map(map<string, int> const &m)
         {
            for (auto const &pair: m) {
                #ifndef __clang__
                std::cout << "{" << pair.first << ": " << pair.second << "}\n";
                #endif
            }
         }
#endif


// int main(){
//     baseIP base;
//     return 0;
// }