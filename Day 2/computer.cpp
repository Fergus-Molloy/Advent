#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "computer.h"

using namespace std;

namespace program{
    vector<string> memory;
    enum INSTRUCTIONS{
        ADD      = 1, // instruction set starts at 1
        MULTIPLY = 2,
        HALT     = 99
    };
    enum IOSTREAM{
        OUTPUT_ADDR = 0,
        NOUN_ADDR   = 1,
        VERB_ADDR   = 2
    };
}


int main(){
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
    return 0;
}

vector<string> split(string text, char delimiter){
    vector<string> tokens;
    int prev=0;
    int pos= text.find(delimiter);
    while(pos!=std::string::npos){
        tokens.push_back(text.substr(prev, pos-prev));
        prev = pos + 1;
        pos = text.find(delimiter, prev);
    }
    return tokens;
}

int str_to_int(string text){
    stringstream ss(text);
    int value;
    ss >> value;
    return value;
}

string readall(string filename){
    ifstream infile(filename);
    stringstream ss;
    ss << infile.rdbuf();
    string data = ss.str();
    infile.close();
    return data;
}

void finish(){
    cout << "Output: " << str_to_int(program::memory[program::OUTPUT_ADDR]) << endl;
    return;
}

int compute(int instruction, int value1, int value2){
    switch(instruction){
        case(program::ADD):
            return value1 + value2;
        case(program::MULTIPLY):
            return value1 * value2;
        case(program::HALT):
            finish();
            return -1;
        default:
            cerr << "Something went wrong instruction read: " << instruction << endl;
            exit(1);
    }
}

void print_instruction(int addr){
        cout << "Instruction:\n" 
        << program::memory[addr]   << ","
        << program::memory[addr+1] << ","
        << program::memory[addr+2] << ","
        << program::memory[addr+3] << endl;
}

void print_decoded_instuction(int inst, int value1, int value2, int addr){
    cout << "Decoded Instruction:\n" 
        << inst   << ","
        << value1 << ","
        << value2 << ","
        << str_to_int(program::memory[addr]) << endl;
}

void run_code_file(string filename){
    string data = readall(filename);
    program::memory = split(data, ',');
    main_loop();
}

void run_code_file(string filename, int noun, int verb){
    string data = readall(filename);
    program::memory = split(data, ',');
    program::memory[program::NOUN_ADDR] = noun;
    program::memory[program::VERB_ADDR] = verb;
    main_loop();
    
}

void main_loop(){
    int result;
    for(int i=0; i<program::memory.size(); i+=4){
        int  inst, var1, var2, addr;
        inst = str_to_int(program::memory[i]);   // instruction
        var1 = str_to_int(program::memory[i+1]); // address of value 1
        var2 = str_to_int(program::memory[i+2]); // address of value 2
        addr = str_to_int(program::memory[i+3]); // address to store at e.g. 0
        
        int value1, value2;
        value1 = str_to_int(program::memory[var1]);
        value2 = str_to_int(program::memory[var2]);
        
        #ifdef DEBUG
        print_instruction(i);
        print_decoded_instruction(inst, value1, value2, addr)        
        #endif
        result = compute(inst, value1, value2);
        if(result != -1)
            program::memory[addr] = to_string(result);
        else
            break;
    }
}