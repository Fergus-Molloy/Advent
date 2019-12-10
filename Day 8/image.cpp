#include <iostream>
#include <vector>
#include <cstring>
#include "../general.h"

#define WIDTH 25
#define HEIGHT 6

using namespace std;

int calc(vector<vector<int>> layers){
    vector<int> fewest_0;
    int min=3200000; 
    int count=0;
    for(auto x : layers){
        count = 0;
        for(auto y : x){
            if(!y)
                count++;
        }
        if(count<min){
            min=count;
            fewest_0 = x;
        }
    }
    int count_1=0;
    int count_2=0;
    for(auto x : fewest_0){
        if(x==1)
            count_1++;
        if(x==2)
            count_2++;
    }
    return count_1*count_2;
}

vector<vector<int>> get_layers(string text){
    vector<vector<int>> layers;
    vector<int> layer;
    int digits_per_layer = WIDTH*HEIGHT;
    int no_layers = text.length()/digits_per_layer;
    for(int j=0; j<no_layers; j++){
        for(int i=j*digits_per_layer; i<digits_per_layer+(j*digits_per_layer); i++){
            layer.push_back(char_to_int(text[i]));
        }
        layers.push_back(layer);
        layer.clear();
    }
    return layers;
}

int main(){
    string text = readall("input.txt");
    vector<vector<int>> layers = get_layers(text);
    string black = "*";
    string white = " ";
    string trans = "t";
    char render[6][25] = {'t'};
    for(int i=0; i<6; i++){
        memset(render[i], 't', 25);
    }

    for(auto layer : layers){
        int x=0, y=0;
        for(int px :layer){
            switch(px){
                case 0:
                    if(render[y][x] == 't')
                        render[y][x] = '#';
                    break;
                case 1:
                    if(render[y][x] == 't')
                        render[y][x] = ' ';
                    break;
                case 2:
                    break;
                default:
                    cerr << "you broke it" << endl;
                    exit(1);
            }
            if(x==WIDTH){
                x=0;
                y++;
            }
            else{
                x++;
            }
        }
    }
    for(int y=0; y<6; y++){
        for(int x=0; x<25; x++){
            cout<<render[y][x];
        }
        cout<<endl;
    }
}