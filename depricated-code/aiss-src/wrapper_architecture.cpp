//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   wrapper_architecture.cpp
// brief  Configuration for Security Wrapper Configuration for using it later for ProtectIP and MelPUF
// date   March 17, 2022
// author kshitijraj@ufl.edu

#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <cmath>
#include "wrapper_config.h"

using namespace std;

void wrapper_config(map<string, int> const &config){
    map<string, int> sw_param_default = {
            { "rstType",  1},
            { "rstSync",  0},
            { "clkEdg",  1},
            { "hasInPortFile",  0},
            { "fanoutHistIsTrue",  0},
            { "activityHistIsTrue",  0},
            {"pufElements",1},
// below parameters dont have a default value. They will be taken from the configuration map. Here, all of them are
// initialized to 0
            { "maxFanout",  0},
            { "nModCell",  0},
            { "HIRApercent",  0},
            { "nFFminPerFSM",  0},
            { "nFFmaxPerFSM",  0},
            { "nFFminPerSubFSM",  0},
            { "nFFmaxPerSubFSM",  0},
            { "reachability",  0},
            { "initSeed",  0},
            { "simFlags",  0},
            {"pufElements",0}
    };

    // Replace default values in parameter fields if they exist in configuration map
    for (auto &item_config : sw_config) {
        if(item_config.first=="nFFminPerFSM"){
            if(item_config.second<3){
                cout<<"nFFminPerFSM value not valid. Please enter value>=3"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        if(item_config.first=="nFFmaxPerFSM"){
            if(item_config.second<sw_config["nFFminPerFSM"]){
                cout<<"nFFmaxPerFSM value not valid. Please enter value>=nFFminPerFSM"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        if(item_config.first=="nFFminPerSubFSM"){
            if(item_config.second<2){
                cout<<"nFFmaxPerFSM value not valid. Please enter value>=2"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        if(item_config.first=="nFFmaxPerSubFSM"){
            if((item_config.second>sw_config["nFFmaxPerFSM"]) || (item_config.second<sw_config["nFFminPerSubFSM"])){
                    cout<<"nFFmaxPerSubFSM value not valid. Please enter value between the range of [nFFminPerSubFSM, nFFmaxPerFSM]"<<endl;
                    exit(EXIT_FAILURE);
                }
        }
        if(item_config.first=="reachability"){
            int comparator =pow(2,sw_config["nFFminPerFSM"])-1;
            if(item_config.second<comparator){
                cout<<"reachability value not valid. Please enter value >= 2^nFFminPerFSM"<<endl;
                exit(EXIT_FAILURE);
            }
        }

        for (auto &item_default: sw_param_default)
            if (item_config.first == item_default.first) {
                 item_default.second = item_config.second;
            };
    }
    cout<<"SSEL did not detect any violations in the wrapper configuration for ProtectIP and ASTRA. This is now be interfaced with ProtectIP and ASTRA to generate configurable security wrappers."<<endl;
    cout<<"Updated configuration parameters for security wrappers are:"<<endl;
    for ( auto &item : sw_param_default) {
        cout << "[" << item.first << "," << item.second << "]\n";
    }
};

int main(){
    wrapper_config(sw_config);
};