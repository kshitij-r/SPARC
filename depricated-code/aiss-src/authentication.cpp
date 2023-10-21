//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   authentication.cpp
// brief  Functions for PUF-based authentication methods
// date   March 12, 2022
// author kshitijraj@ufl.edu

#include "uid.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

void auth_sequence(string uid, double vector) {

// Check if peripheral with given UID exists or not
    if(authentication_uid.find(uid) == authentication_uid.end()){
        cout<<"Peripheral assocciated with given UID does not exist, execution terminated!!";
        exit(EXIT_FAILURE);
    }

// Check if IP is already authenticated
    for (auto& it : authentication_uid) {
        if (it.first == uid) {
            if (it.second == 1) {
                cout << "IP already authenticated!!"<<endl;
            }
        }
    }

// Proceed with unlocking operation by comparing the vectors and updating the status in the map
    for (auto& it : authentication_vector) {
        if (it.first == uid) {
            if (it.second == vector) {
                authentication_uid[uid] = 1;
                cout << "Authentication successful, IP status changed to authenticated!!" << endl;
            }
            else{
                cout << "Authentication unsuccessful, challenge vectors incorrect!!" << endl;
            }
        }
    }
}
