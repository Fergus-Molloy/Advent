#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void complete_day(int day){
    vector<string> lines;
    ifstream infile("TODO.md");
    string line;
    while(getline(infile, line)){
        lines.push_back(line);
    }
    infile.close();

    stringstream fmt;
    fmt << "[x] Day " << day;
    lines[day+1] = fmt.str(); // +1 because of title

    ofstream outfile("TODO.md");
    for(string write : lines){
        outfile<<write<<"\n";
    }
    outfile.close();
}

int main(int argc, char *argv[]){
    int day=0;
    if(argc > 2){
        cerr << "You have entered too many arguments" << endl;;
        exit(1);
    }
    if(argc <=1){
        cerr << "What day have you completed?\n";
        cin >> day;
    }
    if(day == 0){
        stringstream ss(argv[1]);
        if(!(ss >> day)){
            cerr << "Cannot convert to integer" << endl;
        }
    }
    cout << "Completed day " << day << endl;
    complete_day(day);
    return 0;
}