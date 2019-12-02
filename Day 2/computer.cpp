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
        ADD = 1, // instruction set starts at 1
        MULTIPLY = 2,
        HALT=99
    };
}


int main(){
    string data = readall("input.txt");
    program::memory = split(data, ',');
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
        cout << "Instruction:\n" 
        << program::memory[i]   << ","
        << program::memory[i+1] << ","
        << program::memory[i+2] << ","
        << program::memory[i+3] << endl;
        cout << "Decoded Instruction:\n" 
        << str_to_int(program::memory[i])   << ","
        << value1 << ","
        << value2 << ","
        << str_to_int(program::memory[addr]) << endl;
        #endif

        program::memory[addr] = to_string(compute(inst, value1, value2));
    }
    finish();
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
    cout << "Output: " << str_to_int(program::memory[OUTPUT_ADDR]) << endl;
    exit(0);
}

int compute(int instruction, int value1, int value2){
    switch(instruction){
        case(program::ADD):
            return value1 + value2;
        case(program::MULTIPLY):
            return value1 * value2;
        case(program::HALT):
            finish();
        default:
            cerr << "Something went wrong" << endl;
            exit(1);
    }
}