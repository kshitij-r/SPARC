#ifndef DCSUPPLY
#define DCSUPPLY
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class DC_SUPPLY : public slaveIP{

    public:     
        interfaceRegisters supplyDCtoMotor     = {"supplyDCtoMotor","OUTPUT"};
        interfaceRegisters supplyDCtoInterface = {"supplyDCtoInterface","OUTPUT"};
    public:
        void supplyDCpowertoMotor();
        void supplyDCpowertoInterface();
}; 

void DC_SUPPLY::supplyDCpowertoMotor(){
    supplyDCtoMotor.value = 1;
}
void DC_SUPPLY::supplyDCpowertoInterface(){
    supplyDCtoInterface.value = 1;
}
#endif