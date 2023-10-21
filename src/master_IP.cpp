//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   master_IP.cpp
// brief  Code for IP specs in Master configuration
// date   March 12, 2022
// author kshitijraj@ufl.edu

#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include "writetomem.cpp"
using namespace std;

class master : public read_write_to_mem{
public:

    // create the memory map region for this master IP object
    master(string ip_name){
        string prefix = "memory_map_inst_";
        string master_mem_ins = prefix + ip_name;
        cout<<"Memory map created for "<<ip_name<< " with name "<<"''"<<master_mem_ins<<"''"<<endl;
    };

    void print_map(map<string, int> const &m)
    {
        cout<<"Contents of memory map are:"<<endl;
        for (auto const &pair: m) {
            cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }

    void security_req(string auth = "", string ll = ""){
        string authentication = auth;
        string logic_locking = ll;
        bool auth_req = false;
        bool ll_req = false;
        if (auth == "authentication"){
            auth_req = true;
        }
        if (ll == "locked"){
            ll_req = true;
        }
    }
};
