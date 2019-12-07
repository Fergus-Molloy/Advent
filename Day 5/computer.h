#ifndef COMPUTER_D
#define COMPUTER_D
#define RESULT 19690720
#include<string>
#include<vector>

void run_code_file(std::string filename);

void run_code_file(std::string filename, int noun, int verb);

void print_decoded(std::vector<int> inst);

std::vector<int> decode(int instruction);

int get_size(int opcode);

void main_loop();

#endif
