#ifndef CLANGGUARD_H
#define CLANGGUARD_H
#include <string>
// #ifndef __clang__
#include <iostream>
// #endif
using namespace std;
// #ifndef __clang__
void display_to_console(const string message, int loglevel)
{
        if(loglevel == 0)
            cout<<"[ERROR:] "<<message<<endl;
        else if(loglevel == 1)
            cout<<"[WARNING:] "<<message<<endl;
        else if(loglevel == 2)
            cout<<"[INFO:] "<<message<<endl;
}
#else
    #define display_to_console(p1, p2)
// #endif

#ifndef __clang__
void wait_timer(long delay){
    long counter = 1000000000*delay;
    while(counter>0){
        counter--;
    }
}
#else   
    #define wait_timer(p1)
#endif
#endif