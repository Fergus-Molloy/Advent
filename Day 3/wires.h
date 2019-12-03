#ifndef WIRES_D
#define WIRES_D
#include <string>
#include "../general.h"

class Wire{
private:
	void calculatePoints();


	int length;
	std::vector<std::string> path;
	std::vector<Point> points;
    

public:
    Wire();

	Wire(std::vector<std::string> path);

    int getLength();

    std::vector<std::string> getPath();

    void setPath(std::vector<std::string> path);

	std::vector<Point> getPoints();

	int distToPoint(Point p);

};

#endif