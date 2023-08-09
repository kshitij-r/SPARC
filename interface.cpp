#ifndef IFF
#define IFF
#ifndef __clang__
#include <thread>
#include <iostream>
#include <chrono>
#endif
#include <string>
#include "guard.h"
#include <algorithm>
#include <iterator>
#include <array>
#include "sys_map.cpp"
#include <initializer_list>
#include <queue>
#include <map>
#include "map_header.h"

using namespace std;

class INTERFACES : public system_memory_map {
    public:
            struct  interfaceRegisters{
                string name;
                string direction;
                int value;
                bool commitLocalMap;
                array<int, PATHSOURCESIZE> pathSource;
            };

        system_memory_map* localMap = new system_memory_map();
        void displayInterfaceRegister(interfaceRegisters *regName);
        int queryInterfaceRegisters(interfaceRegisters *regName);
        void writeToSelfInterfaceRegister(interfaceRegisters *regName, int newValue);
        void updateDirSelfInterfaceRegister(interfaceRegisters *regName, string direction);
        void writeToExtInterfaceRegister(interfaceRegisters *regName, int newValue);
        // void findUniquePairs(multimap<string, int>& A);
        void mergeMaps(multimap<string, int>& A, multimap<string, int>& B);
        // void printmaps(const multimap<string, int>& myMap);
        void checkPathCoverage();
        
};

void INTERFACES::displayInterfaceRegister(interfaceRegisters *regName){
            string str = regName->name + " DIRECTION: " + regName->direction + " , " +"VALUE: " + to_string(regName->value);
            display_to_console(str,2);
}

int INTERFACES::queryInterfaceRegisters(interfaceRegisters *regName){
        return regName->value;
}

void INTERFACES::writeToSelfInterfaceRegister(interfaceRegisters *regName, int newValue){
    regName->value = newValue;
}

void INTERFACES::updateDirSelfInterfaceRegister(interfaceRegisters *regName, string direction){
    regName->direction = direction;
} 

void INTERFACES::writeToExtInterfaceRegister(interfaceRegisters *regName, int newValue){
    if(regName->direction == "INPUT"){
        string str = "IFF REG " + regName->name + " AND SourceID " + " AND DIRECTION MATCH, UPDATE SUCCESSFUL";
        // display_to_console(str, 2);
        regName->value = newValue;
    }
    else{
        string str = "IFF REG " + regName->name + " AND SourceID " + " AND DIRECTION MISMATCH, UPDATE FAILED";
        // display_to_console(str, 1);
    }
}

// void INTERFACES::findUniquePairs(multimap<string, int>& A) {
//     unordered_map<int, string> *valueToKey;
//     unordered_map<string, int> *keyToValue;
//     multimap<string, int> *uniquePairs;

//     for (auto it = A.begin(); it != A.end(); ++it) {
//         string currentKey = it->first;
//         int currentValue = it->second;

//         // Check if the current value has been seen before
//         auto keyIter = valueToKey->find(currentValue);
//         if (keyIter != valueToKey->end()) {
//             // The current value has been seen before, remove it from uniquePairs
//             auto range = uniquePairs->equal_range(keyIter->second);
//             for (auto rangeIter = range.first; rangeIter != range.second; ++rangeIter) {
//                 if (rangeIter->second == currentValue) {
//                     uniquePairs->erase(rangeIter);
//                     break;
//                 }
//             }
//         } else if (&keyToValue[currentKey] == currentValue) {
//             // The current key-value pair has been seen before, remove it from uniquePairs
//             auto range = uniquePairs->equal_range(currentKey);
//             for (auto rangeIter = range.first; rangeIter != range.second; ++rangeIter) {
//                 if (rangeIter->second == currentValue) {
//                     uniquePairs->erase(rangeIter);
//                     break;
//                 }
//             }
//         } else {
//             // The current key-value pair is unique, add it to uniquePairs
//             uniquePairs->insert(make_pair(currentKey, currentValue));
//             keyToValue[currentKey] = currentValue;
//             valueToKey[currentValue] = currentKey;
//         }
//     }
//     // Check if all the paths are covered
//     if(uniquePairs->empty()){
//             display_to_console("[INTERFACE] ALL PATHS COVERED!", 2);
//         }

//     // Print the unique key-value pairs
//     for (auto it = uniquePairs->begin(); it != uniquePairs->end(); ++it) {
//         string str = "[INTERFACE] PATH " + to_string(it->second) + " NOT COVERED!";
//         display_to_console(str,1);
    
//     }
// }

void INTERFACES::mergeMaps(multimap<string, int>& A, multimap<string, int>& B) {
    A.insert(B.begin(), B.end()); // merge B into A
}

// void INTERFACES::printmaps(const multimap<string, int>& myMap){
//     for(auto const& [key, value] : myMap) {
//         }
// }

void INTERFACES::checkPathCoverage(){
    mergeMaps(*interfaceRegMap, *sourceIDMap);
    // findUniquePairs(*interfaceRegMap);
}
#endif

// int main() {
//     // map_function();
//     return 0;
// }

// int main() {
    
//     INTERFACES::interfaceRegisters CLK = (INTERFACES::interfaceRegisters){"clk","INPUT",1,false,{1,2}};
//     INTERFACES::interfaceRegisters RST = (INTERFACES::interfaceRegisters){"rst","INPUT",376,true,{2,4}};
//     INTERFACES::interfaceRegisters EN = (INTERFACES::interfaceRegisters){"en","INPUT",112,true,{3,7}};
//     INTERFACES TIMER;
//     // TIMER.displayInterfaceRegister(&CLK);
//     // TIMER.commitToFactory({RST, EN});
//     // TIMER.displayInterfaceRegister(&RST);
//     // cout<<"Display 1"<<endl;
//     TIMER.displayInterfaceRegister(&EN);
//     TIMER.writeToExtInterfaceRegister(&EN,101);
//      TIMER.displayInterfaceRegister(&EN);
//     TIMER.queryInterfaceRegisters(&EN);
//     TIMER.writeToSelfInterfaceRegister(&EN, 55);
//     //  TIMER.displayInterfaceRegister(&EN);
//     // TIMER.displayInterfaceRegister(&EN);
//     return 0;
// }