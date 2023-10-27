#ifndef MEMORY_MODEL
#define MEMORY_MODEL
#ifndef __clang__
#include <thread>
#include <iostream>
#include <chrono>
#endif
#include <map>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <assert.h>
// #include <klee/klee.h>
#include "../src/baseIP.cpp"
#include "../headers/guard.h"

using namespace std;

#define MEMORY_SIZE 5 // size of memory 

// class memory_model{
class memory_model: public baseIP{
    private:
        int size = MEMORY_SIZE;
        int count = MEMORY_SIZE;
        int offset = 0;
        int m_clk = 0 ;
        int m_rst = 0;
    public:
        int *memory = new int[size];
        bool fetch_state = false;
        memory_model(){
            for (int i = 0; i < size; i++){
                memory[i] = 0;
            }
            // srand(time(0));
            // while (count!=0)
            //     {
            //         memory[count] = 1 + (rand()%100);
            //         count--;
            //     }
            }
            
        void print_memory_val();
        void delete_from_memory(int clk, int rst, int offset, int base = 0);
        void write_to_memory(int clk, int rst, int offset, int value, int base);
        int *send_data_from_mem(int clk, int rst, int start, int offset = 0);
        void reset_memory();
        bool fetch_sts();
    };

void memory_model::print_memory_val(){
                #ifdef __clang__
                printf("Printing memory values:\n");
                for (int i = 0; i < size; i++)
                {
                    printf("%d ," ,memory[i]);
                    // display_to_console(to_string(memory[i]),2);
                }
                #endif
                #ifndef __clang__
                display_to_console("Printing memory values: ",2);
                for (int i = 0; i < size; i++)
                {
                    display_to_console(to_string(memory[i]),2);
                }
                #endif
            }

int* memory_model::send_data_from_mem(int clk, int rst, int start, int offset){
            int counter = offset;
            int *return_mem = new int[counter+1];
            if (start+offset >= size)
            {
                display_to_console("Illegal memory access!!",0);
                exit(EXIT_FAILURE);
            }
            else if(clk && !rst)
            {
                for (int i=0;i<=counter; i++) {
                    return_mem[i] = memory[start+i];
                        }
            }
            else {
                display_to_console("clk or rst error!!",0);
                exit(EXIT_FAILURE);
            }
            return return_mem;
        }

void memory_model::write_to_memory(int clk, int rst, int offset, int value, int base){
            if (base+offset >= size)
            {
                display_to_console("Memory limit exceeded!!",0);
                exit(EXIT_FAILURE);
            }
            else if(clk && !rst)
            {
                int index = base+offset;
                memory[index] = value;
                display_to_console("Value " + to_string(value) + " written at index " + to_string(index) + " in memory",2);
            }
            else {
                display_to_console("clk or rst error!!",2);
                exit(EXIT_FAILURE);
            }
        }

void memory_model::delete_from_memory(int clk, int rst, int offset, int base){
            if (base+offset >= size)
            {
                display_to_console("Illegal memory access!!",0);
                exit(EXIT_FAILURE);
            }
            else if(clk && !rst)
            {
                int index = base+offset;
                memory[index] = 0;
                display_to_console("Value at index " + to_string(index) + " deleted from memory",2);
            }
            else {
                display_to_console("clk or rst error!!",2);
                exit(EXIT_FAILURE);
            }
        }

void memory_model::reset_memory(){
    for (int i = 0; i < size; i++)
    {
        memory[i] = 10;
    }
    display_to_console("Memory resetted",2);
}

bool memory_model::fetch_sts(){
    if(fetch_state){
        display_to_console("Fetch state true",2);
        return true;
    }
    else{
        display_to_console("Fetching state false",1);
        return false;
    }
}
#endif

// int main(){
//     memory_model* memory_instance = new memory_model;
//     // assert(memory_instance->send_data_from_mem(1,0,0,0)[0] == 11);
//     int *data = memory_instance->send_data_from_mem(1,0,0,3);
//     cout<<data[1]<<endl;
//     // memory_instance->print_memory_val();
//     // memory_instance->fetch_state = false;
//     // memory_instance->fetch_sts();
//     return 0;
// }