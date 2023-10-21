#include <iostream>
#include <cassert>
#include "klee.h"

// -solver-backend=z3
using namespace std;

void proveInequality(){
    // int x;
    int x = klee_int("x");
    // int y = 0;
    // klee_make_symbolic(&x, sizeof(x), "x");
    // // klee_make_symbolic(&y, sizeof(y), "y");
    klee_assume(x>0);
    // klee_assume(x<2147483647);
    assert(x<x+1); 
}


int main(){
    proveInequality();
    return 0;
}