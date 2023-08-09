#ifndef WAIT_STATE
#define WAIT_STATE
#ifndef __clang__
#include <thread>
#include <iostream>
#endif
#include <string>

using namespace std;

bool wait_on_sts(bool value){
    if (!value){
        return true;
    }
    else{
        return false;
    }
}
#endif



// int main(){
//     bool sts;
//     wait_on_sts(sts);
//     wait_on_sts(sts);
//     return 0;
// }