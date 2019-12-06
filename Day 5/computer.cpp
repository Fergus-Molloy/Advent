#include <iostream>
#include <vector>
#include <string>
#include "../general.h"

using namespace std;

namespace program{
    bool run = true;
    vector<int> memory;
    enum ADDRESSING_MODES{
        POSITIONAL = 0,
        DIRECT     = 1
    };
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
}
int main(){


}

void run_code_file(string filename){
    string data = readall(filename);
    program::memory = split_int(data, ',');
    main_loop();
}

// Run the instruction set provided but set the noun and verb before execution
void run_code_file(string filename, int noun, int verb){
    string data = readall(filename);
    program::memory = split_int(data, ',');
    program::memory[program::NOUN_ADDR] = noun;
    program::memory[program::VERB_ADDR] = verb;
    main_loop();
}

vector<int> decode(int instruction){
    string inst = to_string(instruction);
    vector<int> decoded;
    if(inst.length()==1){
        decoded.push_back(instruction);
    }
    else{
        decoded.push_back(stoi(inst.substr(inst.size() - 2)));
        for(int i=inst.length()-3; i > 0; i--){
            if(!stoi(inst.substr(i,1))) // if o
                decoded.push_back(program::POSITIONAL);
            else
                decoded.push_back(program::DIRECT);
        }
    }
    while(decoded.size()!=4){
            decoded.push_back(program::POSITIONAL);
    }
    return decoded;
}
int get_size(int opcode){
    string inst = to_string(opcode);
    int operation = stoi(inst.substr(inst.length()-2));
    switch(operation){
        case(program::ADD):
            return program::ADD_SIZE;
        case(program::MULTIPLY):
            return program::MULTIPLY_SIZE;
        case(program::OUTPUT):
            return program::OUTPUT_SIZE;
        case(program::INPUT):
            return program::INPUT_SIZE;
        case(program::HALT):
            return program::HALT_SIZE;
        default:
            cerr << "uknown instruction, received " << operation << endl;
            return -1;
    }
}

void main_loop(){
    int pc=0;
    vector<int> inst;
    int size;
    int opcode;
    while(program::run){
        opcode = program::memory[pc];
        inst = decode(opcode);
        size = get_size(opcode);
    }
}