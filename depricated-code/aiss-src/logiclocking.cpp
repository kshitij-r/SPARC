//
// Created by Kshitij Raj on 3/9/22.
//

#include "uid.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

void unlocking_sequence(string uid, double keys) {

// Check if peripheral with given UID exists or not
    if(obfucated_uid.find(uid) == obfucated_uid.end()){
        cout<<"Peripheral assocciated with given UID does not exist, execution terminated!!";
        exit(EXIT_FAILURE);
    }

// Check if IP is already unlocked
    for (auto& it : obfucated_uid) {
        if (it.first == uid) {
            if (it.second == 1) {
                cout << "IP already unlocked!!"<<endl;
            }
        }
    }

// Proceed with unlocking operation by comparing the vectors and updating the status in the map
    for (auto& it : obfuscated_keys) {
        if (it.first == uid) {
            if (it.second == keys) {
                obfucated_uid[uid] = 1;
                cout << "Unlocking successful, IP status changed to unlocked!!" << endl;
            }
            else{
                cout << "Unlocking unsuccessful, unlocking keys incorrect!!" << endl;
            }
        }
    }

//    for(auto itr = obfucated_uid.begin(); itr != obfucated_uid.end(); ++itr) {
//        cout << itr->second << endl;
//    }

}
//int main() {
//    unlocking_sequence("UART", 987987);
////    unlocking_sequence("CCU", 123123123123);
//    return 0;
//}