#ifndef COMPUTER_D
#define COMPUTER_D
#define RESULT 19690720
#define OUTPUT_ADDR 0

int str_to_int(std::string text);

int compute(int instruction, int value1, int value2);

void finish();

std::string readall(std::string filename);

std::vector<std::string> split(std::string text, char delimiter);

#endif
