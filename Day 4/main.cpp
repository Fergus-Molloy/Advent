#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../general.h"

bool check_double(int x) {
	std::map<int, int> dict;
	std::string str = std::to_string(x);
	for (int i = 0; i < str.length(); i++) {
		if (dict.find(str[i]) != dict.end()) {
			dict.at(str[i]) += 1;
		}
		else {
			dict.insert({ str[i], 1 });
		}
	}
	for (auto const &str: dict) {
		if (str.second == 2)
			return true;
	}
	return false;
}

bool check_increase(int x) {
	std::string str = std::to_string(x);
	for (int i = 1; i < str.length(); i++) {
		if (str[i - 1] > str[i])
			return false;
	}
	return true;
}

int main() {
	const int floor = 244444;
	const int ceil = 788888;
	std::vector<int> possible_codes;

	for (int x = floor; x < ceil; x++) {
		if (check_double(x)) {
			if (check_increase(x)) {
				possible_codes.push_back(x);
			}
		}
	}
	std::cout << possible_codes.size() << std::endl;
	int i = 0;
}