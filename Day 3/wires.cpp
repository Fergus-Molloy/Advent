#include <iostream>
#include <vector>
#include "wires.h"
#include "../general.h"

using namespace std;

Wire::Wire(){
    length = -1;
    path = "";
}

int Wire::getLength(){return length;}

string Wire::getPath(){return path;}

void Wire::setPath(string path){
    this->path = path;
    length = path.length();
}


int main(){
    vector<string> lines;
    lines = read_file_lines("input.txt");
    Wire wire1;
    Wire wire2;
    for(int i=0; i<lines.size(); i++){
        cout << lines[i] << endl;
    }
}
