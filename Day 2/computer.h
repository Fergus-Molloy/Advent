#ifndef COMPUTER_D
#define COMPUTER_D
#define RESULT 19690720

int str_to_int(std::string text);

int compute(int instruction, int value1, int value2);

void finish();

void run_code_file(std::string filename);

void run_code_file(std::string filename, int noun, int verb);

void main_loop();

std::string readall(std::string filename);

std::vector<std::string> split(std::string text, char delimiter);

#endif
