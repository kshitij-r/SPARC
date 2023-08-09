//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   data_comm.cpp
// brief  Code for sending and receiving data to and from IPs
// date   March 12, 2022
// author kshitijraj@ufl.edu

#include "ip_config.h"
#include "uid.h"
#include "authentication.cpp"
#include "logiclocking.cpp"
#include "slave_IP.cpp"
#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
using namespace std;

class data_transfer : public read_write_to_mem {
    void data_tx(string uid, string reg, int val) {
// Check if IP is master or not, if yes, it can write to any location in the memory map
        if ((master_list.find(uid) == master_list.end()) || (slave_list.find(uid) == slave_list.end())) {
            cout << "Peripheral assocciated with given UID does not exist, transfer unsuccessful!!";
            exit(EXIT_FAILURE);
        }
        // Check status of IP before data transfer
        for (auto &it: authentication_uid) {
            bool auth_flag = false;
            if (it.first == uid) {
                if (it.second != 1) {
                    auth_flag = true;
                }
            }
            if (auth_flag) {
                cout << uid << " not authenticated!!" << endl;
            }
        }
        for (auto &it: obfucated_uid) {
            bool ll_flag = false;
            if (it.first == uid) {
                if (it.second != 1) {
                    ll_flag = true;
                }
            }
            if (ll_flag) {
                cout << uid << " not unlocked!!" << endl;
            }
        }
        write_to_mem(reg, val);
    }
};
