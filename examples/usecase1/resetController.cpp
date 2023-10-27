#ifndef RESET
#define RESET
#include "../../headers/SSEL_HEADER.h"

class RESET_CONTROLLER : public slaveIP{

    public:
        // interfaceRegisters sysRST = {"sysRST","OUTPUT"};
        interfaceRegisters glbRST = {"glbRST","OUTPUT"};
        interfaceRegisters req = {"req","INPUT",0};
    public:
        void issueSysRST();
        void issueGlbRST();
};

///////////////////////////////////////////END OF RESET SPECIFICATION////////////////////////////////////////////

void RESET_CONTROLLER::issueSysRST(){
    // sysRST.value = 1;
    m_ip_rst = false;
    display_to_console("System reset issued", 2);
}

void RESET_CONTROLLER::issueGlbRST(){
    // while(true){
        if(req.value == 1){
            m_ip_rst = false;
            display_to_console("Global reset issued", 2);
            // break;
        }
        // else{
        //     // continue;
        //     // display_to_console("Reset request not asserted", 1);
        // }
        // break;
    // }
}
#endif

// int main(){
//     RESET_CONTROLLER reset_control;
//     reset_control.sysRST.value = 1;
//     reset_control.issueSysRST();
//     reset_control.req.value = 1;
//     reset_control.issueGlbRST();
//     return 0;
// }