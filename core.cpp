#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include <map>
#include "baseIP.cpp"
#include "master_config.cpp"
#include "slave_config.cpp"
using namespace std;


class core : public baseIP{
public:
    void system_lvl_rst(bool rst);
    // bool pcm_auth(slaveIP slave, int challenge_vector);

   

    // bool pcm_auth(slaveIP slave, int unlocking_vector){
    //     if(slave.IP_LOCK_REQ){
    //         if(slave.obf_unlocking_vectors == unlocking_vector){
    //             slave.IP_LOCK_STS = true;
    //             Info("IP unlocking successful");
    //             return true;
    //         }
    //         else{
    //             slave.IP_LOCK_STS = false;
    //             Info("IP unlocking failed");
    //             return false;
    //         }
    //     }
    //     else{
    //         Info("Unlocking for IP instance not required");
    //         return true;
    //     }
    // }

    // void exec_init(string address, int clk, int rst, int state){
    //     //TODO: implement the bootloader code for the core
    // }   

    void poll_sts_busy(int uid, int clk, int rst){
        if(m_sts_busy){
            string str = "IP " + to_string(uid) + " is busy";
            Info(str);
        }
        else{
            string str = "IP " + to_string(uid) + " is not busy";
            Info(str);
        }
    }
};

void core::system_lvl_rst(bool rst){
        if(rst){
        m_sys_rst = true;
        m_sts_busy = false;
        Info("System level reset is asserted");
        Info("System wide busy status is set to false");
        }
    }

    