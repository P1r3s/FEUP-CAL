#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Graph.h"
#include "Position.h"

using namespace std;

int main() {
	map<int, Vertex<Position>> vertices;
	int id;
	double lat, lon;
	Position *pos;
	Vertex<Position> *vertex;
	string line;
	string section;
	ifstream v_file("vertices.txt");
	if (v_file.is_open()) {
		while (getline(v_file, line)) {
			section = line;
			section.erase(section.begin() + section.find(';'), section.end());
			id = stoi(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			lon = stod(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			lat = stod(section);

			pos = new Position(lon, lat);
			vertex = new Vertex<Position>(*pos);
			vertices.insert(pair<int, Vertex<Position> >(id, *vertex));

			cout << id << '\t' << vertices[id].getInfo().getLatDeg() << '\t' << vertices[id].getInfo().getLonDeg() << endl;
			cin.get();
		}
		v_file.close();
	}
	else
		cout << "Unable to open file";
	return 0;
}
