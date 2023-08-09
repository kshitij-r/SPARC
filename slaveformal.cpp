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
#include <set>
#include "guard.h"
#include "baseIP.cpp"
#include "memory_model.cpp"
#include "sys_map.cpp"
#include "interface.cpp"
#include "map_header.h"
// #include "master_config.cpp"
using namespace std;
// static map<string, int> interfaceRegMap;
class slaveIP : public memory_model, public INTERFACES{

    friend class core;
    public:
        // static map<string, int> interfaceRegMap;
        bool m_ip_rst;
        bool FIFO_VALID = false;
        bool ingress_fifo_req = true;
        queue <int> ingress_fifo;
        string myStrings[ENTITYCOUNT];
        // list<string> commitEntityList;
        // list<string> specEntityList;

    public:
        slaveIP(){
            m_ip_rst = false;
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
        void entityRegistry(string mod_name, initializer_list<interfaceRegisters> list);
        // void committoMap(initializer_list<interfaceRegisters> list);
        void checkIntegrationMap();
        void systemIntegration();
        // void checkIntersection();
        void convertp2pToset();
        void convertSysMapToset();
        void checkIOConnection(interfaceRegisters reg1, interfaceRegisters reg2);
        void systemCheck(const list<string>& mylist);
        // void displayvacset();
        // void displaysysset();
        // void displayp2pset();
        // void systemIntegration();
        void read_system_map(string key){
            system_memory_map::read_system_map(key);
        }
        void write_to_system_map(string key, int value){
            system_memory_map::write_to_system_map(key, value);
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
    if(ingress_fifo.size()!=0){
        printf("fifo contents: %d\n", ingress_fifo.front());
        ingress_fifo.pop();
    }
    else{
        printf("FIFO empty\n");
    }
}

void slaveIP::convertp2pToset(){
    for(auto const& [key, value] : p2pmap) {
            p2pToSet.insert(key);
            p2pToSet.insert(value);
            // cout << key << " " << value << endl;
        }
}

void slaveIP::checkIOConnection(interfaceRegisters reg1, interfaceRegisters reg2){
    if(reg1.direction == reg2.direction){
        string str = "[INTEGRATION] " + reg1.name + " AND " + reg2.name + " HAVE SAME DIRECTION!";
        display_to_console(str,1);
    }
}


// void slaveIP::displayp2pset(){
//     for (const auto& str : p2pToSet) {
//     std::cout << str << std::endl;
//     }
// }

// vois slaveIP::systemIntegrationCheck(){}

void slaveIP::entityRegistry(string mod_name, initializer_list<interfaceRegisters> list){
    commitEntityList.push_back(mod_name);
    int intRegCount = 0;
    for (auto element : list){
        // int size = sizeof(element.pathSource) / sizeof(element.pathSource[0]);
        // for (int i=0;i<size;i++){
        //     if(element.pathSource[i]!=0){
        //         interfaceRegMap.insert(std::make_pair(element.name, element.pathSource[i]));
        //     }
        // }
        integrationMap.insert(std::make_pair(element.name, element.direction));
        intRegCount++;
        // countInterfaceRegister.push_back(intRegCount);
        // string str = "[IFR] " + mod_name + " SUCCESSFULLY REGISTERED";
        // display_to_console(str,2);
    }
    // cout<<"Count: "<<intRegCount<<endl;
    countInterfaceRegister.push_back(intRegCount);
    string str = "[IFR] " + mod_name + " SUCCESSFULLY REGISTERED";
    display_to_console(str,2);
}

// void slaveIP::systemCheck(const list<string>& mylist){
//     // std::set_difference(commitEntityList.begin(), commitEntityList.end(), list2.begin(), list2.end(), std::back_inserter(result));
//     // std::set_difference(list2.begin(), list2.end(), list1.begin(), list1.end(), std::back_inserter(result));
    
//     list<string>::iterator itr;
//     itr = mylist.begin();
//     // for(itr; itr!=mylist.end(); itr++ ){
//     //     cout<<*itr<<endl;
//     // }
    
//     // for (const std::string& s : mylist) {
//     //     systemList.push_back(to_string(s));
//     // }
// }

void slaveIP::convertSysMapToset(){
    for(auto const& [key, value] : integrationMap) {
            sysToSet.insert(key);
        }
}

// void slaveIP::displaysysset(){
//     for (const auto& str : sysToSet) {
//     std::cout << str << std::endl;
//     }
// }


void slaveIP::systemIntegration(){
    convertSysMapToset();
    for (auto itr = sysToSet.begin(); itr != sysToSet.end(); ++itr){
        string str = *itr;
        if(p2pToSet.find(str) == p2pToSet.end()){
            string message = "[INTEGRATION] " + str + " CONNECTION NOT FOUND!";
            vacuousPoint.insert(str);
            display_to_console(message,1);
        }
    }
    if(vacuousPoint.begin()==vacuousPoint.end()){
        display_to_console("[INTEGRATION] ALL P2P CONNECTIONS VALID",2);
    }
}

// void slaveIP::displayvacset(){
//     for (const auto& str : vacuousPoint) {
//     std::cout << str << std::endl;
//     }
// }


    



void slaveIP::checkIntegrationMap(){
            map<string, bool> inputKeysFound;
            map<string, bool> outputKeysFound;
            multimap<string, bool> emptyMap;
            
            // Initialize inputKeysFound and outputKeysFound to false
            for (auto& pair : integrationMap) {
                if (pair.second == "INPUT") {
                    inputKeysFound[pair.first] = false;
                } else if (pair.second == "OUTPUT") {
                    outputKeysFound[pair.first] = false;
                }
            }
            
            for (auto i : outputKeysFound){    // search input map from output key
                if (inputKeysFound.find(i.first) == inputKeysFound.end()){
                    string key = i.first;
                    bool value = i.second;
                    emptyMap.insert({key,value});
                }
            }

            for (auto i : inputKeysFound){    // search output map from input key 
                if (outputKeysFound.find(i.first) == outputKeysFound.end()){
                    string key = i.first;
                    bool value = i.second;
                    emptyMap.insert({key,value});
                }
            }
            // for(auto const& [key, value] : emptyMap) {
            //         cout << key << ": " << value << endl;
            //     }
            if(emptyMap.empty()){
                string str = "[INTEGRATION] ALL INTERFACES ESTABLISHED";
                display_to_console(str,2);
            }
            else{
            for(auto const& [key, value] : emptyMap) {
                            string str = "[INTEGRATION] INTERFACE " + key + " CONNECTION NOT FOUND!";
                            display_to_console(str,1);
                            // cout <<"[IFR NOT FOUND] " <<key << ": " << value << endl;
                        }
                }
        }

        // void slaveIP::systemIntegration(){
        //     // for (auto element : list){
        //     //     commitToFactory({element});
        //     //     // integrationMap.insert(std::make_pair(element.name, element.direction));
        //     //     }
        //     checkIntegrationMap();    
        // }
    // for(auto const& [key, value] : interfaceRegMap) {
    //         cout << key << ": " << value << endl;
    //     }
    // for (auto const &pair: interfaceRegMap) {
    //     // #ifndef __clang__
    //     std::cout<<"InterfaceRegMap: " << "{" << pair.first << ": " << pair.second << "}" << "\n";
    //     // #endif
    // }
    // // cout<<"check"<<endl;
    // for (auto const &pair: sourceIDMap) {
    //     // cout<<"inside loop"<<endl;
    //     #ifndef __clang__
    //     std::cout <<"SourceIDMap: "<< "{" << pair.first << ": " << pair.second << "}" << "\n";
    //     #endif
    // }


#endif

// int main(){
//     slaveIP slave1;
//     return 0;
// }