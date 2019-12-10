#ifndef GENERAL_D
#define GENERAL_D

struct Point {
	int x;
	int y;
};

std::vector<int> split_int(std::string text, char delimiter);

std::vector<std::string> split_str(std::string text, char delimiter);

std::string readall(std::string filename);

std::vector<std::string> read_file_lines(std::string filename);

// Convert string to integer
int str_to_int(std::string text);

int char_to_int(char text);

bool operator==(const Point& lhs, const Point& rhs);

#endif