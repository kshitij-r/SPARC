#ifndef TIMER
#define TIMER
#include "../../headers/SSEL_HEADER.h"

class TIMER_CONTROLLER : public slaveIP{

    public:
        interfaceRegisters duration = {"duration","INPUT"};
        interfaceRegisters startTimer = {"startTimer","INPUT"};
        interfaceRegisters timerDone = {"timerDone","OUTPUT"};

    public:
        void timer_start();
        void waiton_Reset();
    
    private:
        bool resetAsserted_ = false;
        bool countdownComplete_ = false;
};

///////////////////////////////////////////END OF TIMER SPECIFICATION////////////////////////////////////////////

void TIMER_CONTROLLER::timer_start(){
    if(m_sts_busy){
        // display_to_console("Timer busy",1);
    }
    else if(resetAsserted_ == true){
        if(startTimer.value == 1){
        m_sts_busy = true;
        int delay = duration.value;
        // delay = delay + 100;
        std::chrono::milliseconds durationMs(delay * 1000);
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start + durationMs;
        while (std::chrono::high_resolution_clock::now() < end) {
            // Do some work...
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds
        }
        m_sts_busy = false;
        timerDone.value = 1;
        countdownComplete_ = true;
        }
    }
}

// void TIMER_CONTROLLER::timerRaiseRequest(){
//     if(countdownComplete_){
//          timerDone.value = 1;
//         //  cout<<"Request Asserted"<<endl;
//     }
// }

void TIMER_CONTROLLER::waiton_Reset(){
    while(true){
        if(m_ip_rst == false){
            resetAsserted_ = true;
            // cout<<"Reset Asserted"<<endl;
            break;
        }
        break;
    }
}

#endif

// int main(){
//     TIMER_CONTROLLER timer;
//     timer.duration.value = 2;
//     timer.startTimer.value = 1;
//     timer.m_ip_rst = false;
//     timer.waiton_Reset();
//     timer.timer_start();
//     timer.timerRaiseRequest();
//     return 0;
// }