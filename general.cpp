#include <sstream>
#include <vector>
#include <fstream>

std::vector<std::string> split(std::string text, char delimiter){
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

std::string readall(std::string filename){
    std::ifstream infile(filename);
    std::stringstream ss;
    ss << infile.rdbuf();
    std::string data = ss.str();
    infile.close();
    return data;
}

std::vector<std::string> read_file_lines(std::string filename){
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> lines;
    while(getline(infile, line)){
        lines.push_back(line);
    }
    return lines;
}
