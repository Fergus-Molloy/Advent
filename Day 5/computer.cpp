#include <iostream>
#include <vector>
#include <string>
#include "computer.h"
#include "../general.h"

using namespace std;

int main(){
    Program prog("input.txt");
    prog.runProgram();

    return 0;
}

Program::Program(std::string filename){
    loadProgram(filename);
}

void Program::loadProgram(std::string filename){
    std::string data = readall(filename);
    memory = split_int(data, ',');
    dataRegisters.push_back(&dr1);
    dataRegisters.push_back(&dr2);
    pc = 0;
    run = true;
}

void Program::runProgram(){
    while(run){
        fetch();
        decode();
    }
}

void Program::fetch(){
    ir = memory[pc];
    vector<int> datamodes;
    instruction = (ir) % 100;
    datamodes.push_back((ir / 100) % 10);
    datamodes.push_back((ir / 1000) % 10);

    for(int i=1; i<dataRegisters.size()+1; i++){
        if(datamodes[i-1]==1)
            *dataRegisters[i-1] = memory[pc+i];
        else
            *dataRegisters[i-1] = (memory[memory[pc+i]]);
    }

}

void Program::decode(){
    switch(instruction){
        case codes::ADD:
            out = memory[pc+3];
            executeAdd();
            pc += codes::ADD_SIZE;
        break;
        case codes::MULTIPLY:
            out = memory[pc+3];
            executeMultiply();
            pc += codes::MULTIPLY_SIZE;
        break;
        case codes::INPUT:
            out = memory[pc+1];
            executeInput();
            pc += codes::INPUT_SIZE;
        break;
        case codes::OUTPUT:
            out = memory[pc+1];
            executeOutput();
            pc += codes::OUTPUT_SIZE;
        break;
        case codes::JIT:
            pc += codes::JIT_SIZE; // do this first because if value is false
            executeJIT();          // we don't want to increment pc after the jump
        break;
        case codes::JIF:
            pc += codes::JIF_SIZE;
            executeJIF();
        break;
        case codes::LESS:
            out = memory[pc+3];
            executeLess();
            pc += codes::LESS_SIZE;
        break;
        case codes::EQU:
            out = memory[pc+3];
            executeEqu();
            pc += codes::EQU_SIZE;
        break;
        case codes::HALT:
            out = codes::OUTPUT_ADDR;
            executeHalt();
            pc += codes::HALT_SIZE;
        break;
        default:
            cerr << "you broke it" << endl;
            exit(1);
    }
}

void Program::executeAdd(){
    memory[out] = dr1 + dr2;
}

void Program::executeMultiply(){
    memory[out] = dr1 * dr2;
}

void Program::executeInput(){
    cout << "Input a number: " << endl;
    int input;
    cin>>input;
    memory[out] = input;
}

void Program::executeOutput(){
    cout << "Output:\n"
        << memory[out] << endl;
}

void Program::executeJIT(){
    if(dr1){
        pc = dr2;
    }
}

void Program::executeJIF(){
    if(!dr1){
        pc = dr2;
    }
}

void Program::executeLess(){
    if(dr1 < dr2){
        memory[out] = 1;
    }
    else{
        memory[out] = 0;
    }
}

void Program::executeEqu(){
    
    if(dr1 == dr2){
        memory[out] = 1;
    }
    else{
        memory[out] = 0;
    }
}

void Program::executeHalt(){
    run = false;
    cout << "Result:" << memory[out] << endl;
}
