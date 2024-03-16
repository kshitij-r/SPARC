#ifndef DCSUPPLY
#define DCSUPPLY
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class DC_SUPPLY : public slaveIP{

    public:     
        interfaceRegisters supplyDCtoMotor = {"supplyDCtoMotor","OUTPUT"};
        interfaceRegisters supplyDCtoInterface = {"supplyDCtoInterface","OUTPUT"};
    public:
        void supplyDCpower();
}; 

void DC_SUPPLY::supplyDCpower(){
    supplyDCtoMotor.value = 1;
    supplyDCtoInterface.value = 1;
}
#endif