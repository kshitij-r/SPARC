//
//    AISS CONFIDENTIAL - INTERNAL USE ONLY
//
//	         Copyright by University of Florida, 2022
//
//			 All rights reserved.
//	         Copyright does not imply publication.
//
// file   ip_config.h
// brief  Memory map of system SoC
// date   March 12, 2022
// author kshitijraj@ufl.edu



#ifndef SSEL_MEMORY_TRANSACTION_H
#define SSEL_MEMORY_TRANSACTION_H

#endif //SSEL_MEMORY_TRANSACTION_H

#include <iostream>
#include <string>
#include <map>

using namespace std;
// Reset values of memory mapped CCU registers
map<string , int> r_ccu = {
        { "0x30000000",  0},
        { "0x30000004",  0},
        { "0x30000008",  0},
        { "0x3000000A",  0},
        { "0x3000000C",  0},
        { "0x30000010",  0},
};
// Reset values of memory mapped PCM registers
map<string , int> r_puf_control_module = {
        { "0x31000000",  0},
        { "0x31000004",  0},
        { "0x31000008",  0},
        { "0x3100000A",  0},
        { "0x3100000C",  0},
        { "0x31000010",  0},
};
// Reset values of memory mapped LL registers
map<string , int> r_ll_module = {
        { "0x32000000",  0},
        { "0x32000004",  0},
        { "0x32000008",  0},
};
// Reset values of memory mapped UART registers
map<string , int> r_uart = {
        { "0x33000000",  0},
        { "0x33000004",  0},
        { "0x33000008",  0},
        { "0x3300000A",  0},
        { "0x3300000C",  0},
        { "0x33000010",  0},
};
// Reset values of memory mapped GPIO registers
map<string , int> r_gpio = {
        { "0x34000000",  0},
        { "0x34000004",  0},
        { "0x34000008",  0},
        { "0x3400000A",  0},
        { "0x3400000C",  0},
        { "0x34000010",  0},
};
// Post-reset SoC transactions
map<string , double> soc_op = {
        { "0x30000000",  1},  /////////////////////
        { "0x30000004",  1},  /////////////////////
        { "0x30000008",  1},  //// CCU registers //
        { "0x3000000A",  0},  /////////////////////
        { "0x3000000C",  1},  /////////////////////
        { "0x30000010",  1},  /////////////////////

        { "0x31000000",  1},                        /////////////////////
        { "0x31000004",  0},                        /////////////////////
        { "0x31000008",  1},                        /////////////////////
        { "0x3100000A",  1100110101010101000},      //// PCM registers //
        { "0x3100000C",  0},                        /////////////////////
        { "0x31000010",  1},                        /////////////////////

        { "0x32000000",  1},                        /////////////////////
        { "0x32000004",  1100111001002011001},      //// LL registers ///
        { "0x32000008",  1},                        /////////////////////

        { "0x34000000",  1},                        /////////////////////
        { "0x34000004",  1},                        /////////////////////
        { "0x34000008",  0},                        /////////////////////
        { "0x3400000A",  1},                        /// GPIO registers //
        { "0x3400000C",  1},                        /////////////////////
        { "0x34000010",  1},                        /////////////////////
};