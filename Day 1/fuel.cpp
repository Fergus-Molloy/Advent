#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

int fuel(int mass){
    double fuel_amount;
    fuel_amount = mass/3.0;
    fuel_amount = floor(fuel_amount) - 2;
    if(fuel_amount<=0)
        return 0;
    return (int) (fuel_amount + fuel(fuel_amount));
}

int main(){
    ifstream infile("input.txt");
    string line;
    int sum=0;
    int temp;
    while(getline(infile, line)){
        cout << "mass: " << line << endl;
        stringstream value(line);
        value >> temp;
        temp = fuel(temp);
        cout << "fuel: " << temp << endl;
        sum += temp;
    }
    cout << "total fuel: " << sum << endl;
    
    return 0;
}
