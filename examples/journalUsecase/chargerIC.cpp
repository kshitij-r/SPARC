#ifndef CHARGERIC
#define CHARGERIC
#include "../../headers/SSEL_HEADER.h"

using namespace std;

class CHARGER_IC : public slaveIP{

    public:     
        interfaceRegisters supplyPower = {"supplyPower","OUTPUT"};
    public:
        void supplyICpower();
}; 

void CHARGER_IC::supplyICpower(){
    supplyPower.value = 1;
}
#endif

// int main(){
//     CHARGER_IC cic;
//     cic.supplyICpower();
// }