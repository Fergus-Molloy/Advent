#ifndef COMPUTER_D
#define COMPUTER_D
#include <vector>
#include "../general.h"

// namespace for all the constants i use to add readability
namespace codes{
    enum ADDRESSING_MODES{
        POSITIONAL = 0,
        DIRECT     = 1
    };

    enum INSTRUCTIONS{
        ADD      = 1, // instruction set
        MULTIPLY = 2,
        INPUT    = 3,
        OUTPUT   = 4,
        JIT      = 5,
        JIF      = 6,
        LESS     = 7,
        EQU      = 8,
        HALT     = 99
    };
    enum IOSTREAM{
        OUTPUT_ADDR = 0, // addrs values for output and input values
        NOUN_ADDR   = 1,
        VERB_ADDR   = 2
    };
    enum SIZES{
        ADD_SIZE      = 4, //sizes of each instruction to add to pc
        MULTIPLY_SIZE = 4,
        INPUT_SIZE    = 2,
        OUTPUT_SIZE   = 2,
        JIT_SIZE      = 3,
        JIF_SIZE      = 3,
        LESS_SIZE     = 4,
        EQU_SIZE      = 4,
        HALT_SIZE     = 1
    };
}

class Program{
private:
//registers: pc = Program counter, ir=instruction register,  drX = data register X, out = output address
    int pc, ir, dr1, dr2, out;
    bool run; // flag for if the program should halt
    int instruction; // for passing instruction from decode to execute
    std::vector<int> memory; //holds all the data for the program
    std::vector<int*> dataRegisters; //array for iterating over the data registers

    void fetch();

    void decode();

    void executeAdd();

    void executeMultiply();

    void executeInput();

    void executeOutput();

    void executeJIT();

    void executeJIF();

    void executeLess();

    void executeEqu();

    void executeHalt();

public:
    Program();

    Program(std::string filename);

    void loadProgram(std::string filename);

    void runProgram();

};
#endif
