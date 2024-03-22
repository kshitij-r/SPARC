#ifndef USER_IN
#define USER_IN
#include "../../headers/SPARC_JOURNAL.h"

using namespace std;

class USER_INPUT : public slaveIP{

    public:     
        interfaceRegisters inputToInterface = {"inputToInterface","OUTPUT"};
    private:
        int seed = 0;
    public:
        void commandToInterface();
}; 

void USER_INPUT::commandToInterface(){
    seed = seed + 1;
    // klee_make_symbolic(&inputToInterface.value, sizeof(inputToInterface.value), "inputToInterface.value");
    // if(seed%4 == 0){
    //     inputToInterface.value = 0;
    // }
    // else {
    //     inputToInterface.value = 1;
    // }
    inputToInterface.value = 1;
}
#endif