#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h> //for reverse()
#include "computer.h"
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
    run_code_file("input2.txt");
    return 0;
}

vector<int> decode(int instruction){
    string inst = to_string(instruction);
    reverse(inst.begin(), inst.end());
    vector<int> decoded;
    if(inst.length()==1){
        decoded.push_back(instruction);
    }
    else{
        for (int i=0; i<inst.length(); i++){
            if(i==1)
                continue;
            decoded.push_back(inst[i]-'0');
        }
    }
    while(decoded.size()!=4){
            decoded.push_back(program::POSITIONAL);
    }
    return decoded;
}
int get_size(int opcode){
    switch(opcode){
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
            cerr << "uknown instruction, received " << opcode << endl;
            return -1;
    }
}

void execute(vector<int> inst, int size, int pc){
    vector<int> data;
    for(int i=1; i<inst.size(); i++){ //get relevant data
        if(!inst[i]){
            //position mode
            data.push_back(program::memory[program::memory[pc+i]]);
        }
        else{
            //immediate mode
            data.push_back(program::memory[pc+i]);
        }
    }
    switch(inst[0]){
        case(1):
            add(data);
        break;
        case(2):
            multiply(data);
        break;
        case(3):
            input(data);
        break;
        case(4):
            output(data);
        break;
        case(99):
            halt();
        break;
        default:
            cerr << "Unknown instruction " << inst[0] << endl;

    }
}

void print_decoded(vector<int> inst){
    for(int x=0; x<inst.size(); x++){
        cout << inst[x] << " , ";
    }
    cout << endl;
}

void main_loop(){
    int pc=0;
    vector<int> inst;
    int size;
    int opcode;
    while(program::run){
        opcode = program::memory[pc];
        inst = decode(opcode);
        print_decoded(inst);
        size = get_size(inst[0]);
        //execute(inst, size, pc);
        program::run = false;
    }
}

// ----- RUN CODE FILE -----
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