#include <assert.h>
#include "../../../../headers/SPARC_HEADER.h"

using namespace std;
RESET_CONTROLLER* reset_control = new RESET_CONTROLLER;
CRC_CONTROLLER* crc = new CRC_CONTROLLER;

int main(){
    int x;
    assert(x==12345);

    return 0;
}