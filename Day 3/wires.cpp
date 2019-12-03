#include <iostream>
#include <vector>
#include "wires.h"
#include "../general.h"


Wire::Wire(){
    length = -1;
    std::vector<std::string> path;
}

Wire::Wire(std::vector<std::string> path) {
	this->path = path;
	length = path.size();
	calculatePoints();
}

int Wire::getLength(){return length;}

std::vector<std::string> Wire::getPath(){return path;}

std::vector<Point> Wire::getPoints() { return points;}

void Wire::calculatePoints() {
	Point point;
	point.x = 0;
	point.y = 0;
	points.push_back(point);
	
	for (int i = 1; i < path.size()+1; i++) {
		char c = path[i-1][0]; // first character in wire
		int amount;
		amount = str_to_int(path[i-1].substr(1));

		for (int j = 0; j < amount; j++) {
			Point new_point = { points.back().x, points.back().y }; //create a copy of previous point
			switch (c) {
			case('U'):
				//go up
				new_point.y++;
				points.push_back(new_point);
				break;
			case('D'):
				//go down
				new_point.y--;
				points.push_back(new_point);
				break;
			case('R'):
				//go right
				new_point.x++;
				points.push_back(new_point);
				break;
			case('L'):
				//go left
				new_point.x--;
				points.push_back(new_point);
				break;
			default:
				std::cerr << "Direction " << c << " not recognised" << std::endl;
				break;
			}
		}
#ifdef DEBUG
		std::cout << "point[i-1]: " << points[i - 1].x << " , " << points[i - 1].y << "\n"
				  << "point[i]: " << points[i].x << " , " << points[i].y << std::endl;
#endif
	}
}

int Wire::distToPoint(Point p) {
	Point curr{ 0,0 };
	for (int i = 0; i < points.size(); i++) {
		curr = points[i];
		if (curr == p)
			return i;
	}
	return -1;
}

void Wire::setPath(std::vector<std::string> in_path){
    path = in_path;
    length = path.size();
	calculatePoints();
}

