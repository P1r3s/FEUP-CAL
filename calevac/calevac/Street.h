#pragma once

#include <string>

using namespace std;

class Street
{
	string name;
	bool twoway;
public:
	Street() { name = ""; twoway = true; };
	Street(string n, bool t);
	string getName() {
		return name;
	};
	double isTwoWay() {
		return twoway;
	};
};

Street::Street(string n, bool t)
{
	name = n;
	twoway = t;
}