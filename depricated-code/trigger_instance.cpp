//
// Created by Kshitij Raj on 6/7/22.
//
#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <chrono>
#include <thread>
#include "uid.h"
using namespace std;

void time_delay(int delay, string unit){
    auto start = chrono::high_resolution_clock::now();
    if(unit == "seconds"){
        std::this_thread::sleep_for(std::chrono::seconds (delay));}
    else if(unit == "milliseconds"){
        std::this_thread::sleep_for(std::chrono::milliseconds (delay));}
    else if(unit == "nanoseconds"){
        std::this_thread::sleep_for(std::chrono::nanoseconds(delay));}
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout<<"delay is: "<<duration.count()<<unit<<endl;
}

void system_entity_status(string uid, int status){
    // Check if peripheral with given UID exists or not
    if(entity_status.find(uid) == entity_status.end()){
        cout<<"Peripheral assocciated with given UID does not exist, execution terminated!!";
        exit(EXIT_FAILURE);
    }
    // Change status of IP (active <---> inactive)
    for (auto& it : entity_status) {
        if (it.first == uid) {
            it.second = status;
                cout << "IP status changed" << endl;
            }
        else{
                cout << "IP UID incorrect, status unchanged!!" << endl;
            }
        }
    }

// void system_event_trigger(const string& signal, string uid_1, const string& uid_2 = "", int value = 0){

// }

//
//int payload_trigger(){
//    return 0;
//}

int main(){
    time_delay(4, "seconds");
    return 0;
}
