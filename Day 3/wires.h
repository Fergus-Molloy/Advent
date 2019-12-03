#ifndef WIRES_D
#define WIRES_D
#include <string>

class Wire{
    public:
    Wire();

    int getLength();

    std::string getPath();

    void setPath(std::string path);


    private:
    int length;
    std::string path;
};



#endif