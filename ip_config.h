//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   ip_config.h
// brief  Configuration file for IPs integrated
// date   March 12, 2022
// author kshitijraj@ufl.edu

#ifndef SSEL_IP_CONFIG_H
#define SSEL_IP_CONFIG_H
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> master_list = {
        { "CCU",  1}
};
map<string, int> slave_list = {
        { "UART",  1},
        { "GPIO",  2},
        { "PCM",  3}
};
#endif //SSEL_IP_CONFIG_H
