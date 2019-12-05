#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "../general.h"
#include "computer.h"

using namespace std;

namespace program{
    //instruction:      DE   C    B    A
    typedef std::tuple<int, int, int, int> inst_tuple;
    vector<string> memory;
    bool run = true;
    enum INSTRUCTIONS{
        ADD      = 1, // instruction set
        MULTIPLY = 2,
        INPUT    = 3,
        OUTPUT   = 4,
        HALT     = 99
    };
    enum IOSTREAM{
        OUTPUT_ADDR = 0, // addrs values for output and input values
        NOUN_ADDR   = 1,
        VERB_ADDR   = 2
    };
    enum SIZES{
        ADD_SIZE      = 4,
        MULTIPLY_SIZE = 4,
        INPUT_SIZE    = 2,
        OUTPUT_SIZE   = 2,
        HALT_SIZE     = 1
    };

    void add(int value1, int value2, int addr){
        memory[addr] = value1 + value2;
    }
    void multiply(int value1, int value2, int addr){
        memory[addr] = value1 * value2;
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

int main(){
    int output;
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            run_code_file("input.txt", i, j);
            output = str_to_int(program::memory[program::OUTPUT_ADDR]);
            if(output==RESULT){
                cout << "i: " << i << " j: " << j << endl;
                std::exit(0);
            }
        }
    }

    return 0;
}


void finish(){
    int result = str_to_int(program::memory[program::OUTPUT_ADDR]);
    cout << "Output: " << result << endl;
    if(result==RESULT){
        cout << "found the result" << endl;
    }
    program::run = false;
    return;
}

int get_size(string instruction){
    //get last 2 characters
    int operation = str_to_int(instruction.substr(instruction.size() - 2));
    switch(operation){
        case(program::ADD):
            return program::ADD_SIZE;
        case(program::MULTIPLY):
            return program::MULTIPLY_SIZE;
        case(program::INPUT):
            return program::INPUT_SIZE;
        case(program::OUTPUT):
            return program::OUTPUT_SIZE;
        case(program::HALT):
            return program::HALT_SIZE;
        default:
            cerr << "Something went wrong instruction read: " << instruction << endl;
            std::exit(1);
    }
}


// Does the computation for the given instruction
int compute(int instruction, vector<int> values){
    int out;
    switch(instruction){
        case(program::ADD):
            if(values.size() != 2){
                cerr<< "incorrect number of vairables to add" << endl;
                std::exit(1);
            }
            out = values[0];
            out += values[1];
            return out;
        case(program::MULTIPLY):
            if(values.size() != 2){
                cerr<< "incorrect number of vairables to multiply" << endl;
                std::exit(1);
            }
            out = values[0];
            out *= values[1];
            return out;
        case(program::INPUT):
            if(values.size() != 1){
                cerr<< "incorrect number of vairables to input" << endl;
                std::exit(1);
            }
            out = values[0];
            return out;
        case(program::OUTPUT):
            if(values.size() != 1){
                cerr<< "incorrect number of vairables to input" << endl;
                std::exit(1);
            }
            out = values[0];
            return out;
        case(program::HALT):
            // TODO: find a better way of halting
            finish();
            break;
        default:
            cerr << "Something went wrong instruction read: " << instruction << endl;
            std::exit(1);
    }
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
    program::memory[program::NOUN_ADDR] = to_string(noun);
    program::memory[program::VERB_ADDR] = to_string(verb);
    main_loop();
}

// Steps through the program loaded in memory and executes it
void main_loop(){
    int result;
    int previous;
    int pc=0; //program counter
    while(program::run){
        if(pc >= program::memory.size()){
            finish();
        }
        //read the instruction, memory locations for values and
        //the memory location for storing the address
        int  inst, var1, var2, addr;
        inst = str_to_int(program::memory[pc]);   // instruction
        //TODO: decode instruction here
        var1 = str_to_int(program::memory[pc+1]); // address of value 1
        var2 = str_to_int(program::memory[pc+2]); // address of value 2
        addr = str_to_int(program::memory[pc+3]); // address to store at e.g. 0
        
        //value to use for computation
        int value1, value2;
        value1 = str_to_int(program::memory[var1]);
        value2 = str_to_int(program::memory[var2]);
        
        #ifdef DEBUG
        print_instruction(pc);
        print_decoded_instruction(inst, value1, value2, addr)        
        #endif

        result = compute(inst, value1, value2);
        if(program::run) //if halt wasn't called
            program::memory[addr] = to_string(result);
        else
            finish(); // loop will exit after finish
        pc += get_size(program::memory[pc]); // add size of instruction to pc
    }
}