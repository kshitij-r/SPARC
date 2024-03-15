#ifndef DCSUPPLY
#define DCSUPPLY
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class DC_SUPPLY : public slaveIP{

    public:     
        interfaceRegisters supplyDC = {"supplyDC","OUTPUT"};
    public:
        void supplyDCpower();
}; 

void DC_SUPPLY::supplyDCpower(){
    supplyDC.value = 1;
}
#endif