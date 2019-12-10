#include <sstream>
#include <vector>
#include <fstream>
#include "general.h"

std::vector<std::string> split_str(std::string text, char delimiter){
    std::vector<std::string> tokens;
    int prev=0;
    int pos= text.find(delimiter);
    while(pos!=std::string::npos){
        tokens.push_back(text.substr(prev, pos-prev));
        prev = pos + 1;
        pos = text.find(delimiter, prev);
    }
    return tokens;
}

std::vector<int> split_int(std::string text, char delimiter){
    std::vector<int> tokens;
    int prev=0;
    int pos= text.find(delimiter);
    while(pos!=std::string::npos){
        tokens.push_back(str_to_int(text.substr(prev, pos-prev)));
        prev = pos + 1;
        pos = text.find(delimiter, prev);
    }
    return tokens;
}

std::string readall(std::string filename){
    std::ifstream infile(filename);
	if (!infile)
		throw "Couldn't open file\n";
    std::stringstream ss;
    ss << infile.rdbuf();
    std::string data = ss.str();
    infile.close();
    return data;
}

std::vector<std::string> read_file_lines(std::string filename){
    std::ifstream infile(filename);
	if (!infile)
		throw "Couldn't open file\n";
    std::string line;
    std::vector<std::string> lines;
    while(getline(infile, line)){
        lines.push_back(line);
    }
	infile.close();
    return lines;
}

// Convert string to integer
int str_to_int(std::string text) {
	std::stringstream ss(text);
	int value;
	ss >> value;
	return value;
}

// Convert string to integer
int char_to_int(char text) {
    if(text<48 || text>58){
        throw "character is not a number";
        exit(1);
    }
	return text - '0';
}

bool operator==(const Point& lhs, const Point& rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}