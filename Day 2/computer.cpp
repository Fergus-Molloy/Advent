#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "../general.h"
#include "computer.h"

using namespace std;

namespace program{
    vector<string> memory;
    enum INSTRUCTIONS{
        ADD      = 1, // instruction set
        MULTIPLY = 2,
        HALT     = 99
    };
    enum IOSTREAM{
        OUTPUT_ADDR = 0, // addrs values for output and input values
        NOUN_ADDR   = 1,
        VERB_ADDR   = 2
    };
}


int main(){
    run_code_file("input2.txt", 89, 9);
    /*
    int output;
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            run_code_file("input.txt", i, j);
            output = str_to_int(program::memory[program::OUTPUT_ADDR]);
            if(output==RESULT){
                cout << "i: " << i << " j: " << j << endl;
                exit(0);
            }
        }
    }
    */
    return 0;
}


void finish(){
    int result = str_to_int(program::memory[program::OUTPUT_ADDR]);
    cout << "Output: " << result << endl;
    if(result==RESULT){
        cout << "found the result" << endl;
    }
    return;
}

// Does the computation for the given instruction
int compute(int instruction, int value1, int value2){
    switch(instruction){
        case(program::ADD):
            return value1 + value2;
        case(program::MULTIPLY):
            return value1 * value2;
        case(program::HALT):
            // TODO: find a better way of halting
            finish();
            return -1;
        default:
            cerr << "Something went wrong instruction read: " << instruction << endl;
            exit(1);
    }
}

// Print the instruction at a given location --For debuging use
void print_instruction(int addr){
        cout << "Instruction:\n" 
        << program::memory[addr]   << ","
        << program::memory[addr+1] << ","
        << program::memory[addr+2] << ","
        << program::memory[addr+3] << endl;
}

// Print the decoded instruction at a given location --For debuging use
void print_decoded_instuction(int inst, int value1, int value2, int addr){
    cout << "Decoded Instruction:\n" 
        << inst   << ","
        << value1 << ","
        << value2 << ","
        << str_to_int(program::memory[addr]) << endl;
}

// Run the instruction set provided in the file
void run_code_file(string filename){
    string data = readall(filename);
    program::memory = split(data, ',');
    main_loop();
}

// Run the instruction set provided but set the noun and verb before execution
void run_code_file(string filename, int noun, int verb){
    string data = readall(filename);
    program::memory = split(data, ',');
    program::memory[program::NOUN_ADDR] = noun;
    program::memory[program::VERB_ADDR] = verb;
    main_loop();
    
}

// Steps through the program loaded in memory and executes it
void main_loop(){
    int result;
    for(int i=0; i<program::memory.size(); i+=4){
        //read the instruction, memory locations for values and
        //the memory location for storing the address
        int  inst, var1, var2, addr;
        inst = str_to_int(program::memory[i]);   // instruction
        var1 = str_to_int(program::memory[i+1]); // address of value 1
        var2 = str_to_int(program::memory[i+2]); // address of value 2
        addr = str_to_int(program::memory[i+3]); // address to store at e.g. 0
        
        //value to use for computation
        int value1, value2;
        value1 = str_to_int(program::memory[var1]);
        value2 = str_to_int(program::memory[var2]);
        
        #ifdef DEBUG
        print_instruction(i);
        print_decoded_instruction(inst, value1, value2, addr)        
        #endif

        result = compute(inst, value1, value2);
        if(result != -1) //if halt was called
            program::memory[addr] = to_string(result);
        else
            break;
    }
}