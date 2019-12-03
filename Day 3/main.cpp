#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "wires.h"
#include "../general.h"

using namespace std;


std::vector<Point> intersectPoints(const std::vector<Point> points1, const std::vector<Point> points2) {
	std::vector<Point> interects;
	Point p{ 0,0 };
	interects.push_back(p);

	for (auto point1 : points1) {
		if (find(points2.begin(), points2.end(), point1) != points2.end() 
			&& find(interects.begin(), interects.end(), point1) == interects.end()) {
				interects.push_back(point1);
		}
	}
	return interects;
}

int min(vector<int> values) {
	int16_t min = INT16_MAX;
	for (auto value : values) {
		if (value < min)
			min = value;
	}
	return min;
}

//calculate distance from origin to point
int manhattan_distance(Point p) {
	return abs(p.x) + abs(p.y);
}

vector<int> calc_distances(vector<Point> points) {
	vector<int> dist;
	for (auto p : points) {
		dist.push_back(manhattan_distance(p));
	}
	return dist;
}

int main() {
	vector<string> lines = read_file_lines("Day 3/input.txt");
	Wire wire1(split(lines[0], ','));
	Wire wire2(split(lines[1], ','));
	
	vector<Point> intersects = intersectPoints(wire1.getPoints(), wire2.getPoints());
	intersects.erase(intersects.begin()); // remove 0,0 from intersects

	vector<int> distances1, distances2;
	for (auto intersect : intersects) {
		distances1.push_back(wire1.distToPoint(intersect));
		distances2.push_back(wire2.distToPoint(intersect));
	}
	
	vector<int> total_distances;
	for (int x = 0; x < distances1.size(); x++) {
		total_distances.push_back(distances1[x] + distances2[x]);
	}
	int smallest = min(total_distances);

	cout << smallest << endl;
}