#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "Graph.h"
#include "Position.h"
#include "Street.h"

using namespace std;

int main() {
	map<int, Position> positions;
	double minx= numeric_limits<double>::max(), miny = numeric_limits<double>::max(), maxx = -numeric_limits<double>::max(), maxy = -numeric_limits<double>::max();
	long long id;
	double lat, lon;
	Position *pos;
	string line;
	string section;
	ifstream v_file("vertices.txt");
	if (v_file.is_open()) {
		while (getline(v_file, line)) {
			section = line;
			section.erase(section.begin() + section.find(';'), section.end());
			id = stoll(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			lon = stod(section);

			if (lon < minx)
				minx = lon;
			if (lon > maxx)
				maxx = lon;

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			lat = stod(section);

			if (lat < miny)
				miny = lat;
			if (lat > maxy)
				maxy = lat;

			pos = new Position(lon, lat);
			positions.insert(pair<int, Position>(id, *pos));

			//cout << id << '\t' << vertices[id].getInfo().getLatDeg() << endl;
			//cin.get();
		}
		v_file.close();
	}
	else
		cout << "Unable to open vertex file";

	cout << minx << '\t' << maxx << '\t' << miny << '\t' << maxy << endl;
	cin.get();
	cout << "over" << endl;
	map<int, Street> streets;
	string name;
	bool twoway;
	Street *street;
	ifstream e_file("edges.txt");
	if (e_file.is_open()) {
		while (getline(e_file, line)) {
			section = line;
			section.erase(section.begin() + section.find(';'), section.end());
			id = stoll(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			name = section;

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			//section.erase(section.begin() + section.find(';'), section.end());
			if (section == "True")
				twoway = true;
			else
				twoway = false;

			street = new Street(name, twoway);
			streets.insert(pair<int, Street>(id, *street));
		}
		e_file.close();
	}
	else
		cout << "Unable to open edge file";

	cout << "over" << endl;
	Graph<Position> g;
	Vertex<Position> *v1, *v2;
	Edge<Position> *e;
	long long idv1, idv2;
	ifstream g_file("graph.txt");
	if (g_file.is_open()) {
		while (getline(g_file, line)) {
			section = line;
			section.erase(section.begin() + section.find(';'), section.end());
			id = stoll(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin() + section.find(';'), section.end());
			idv1 = stoll(section);

			section = line;
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			section.erase(section.begin(), section.begin() + section.find(';') + 1);
			//section.erase(section.begin() + section.find(';'), section.end());
			idv2 = stoll(section);

			/*v1 = new Vertex<Position>(positions[idv1]);
			v2 = new Vertex<Position>(positions[idv2]);
			e = new Edge<Position>(v2, 1, streets[id].getName(), streets[id].isTwoWay());*/
			g.addVertex(positions[idv1]);
			g.addVertex(positions[idv2]);
			g.addEdge(positions[idv1], positions[idv2], positions[idv1].getDist(positions[idv2]));
			if(streets[id].isTwoWay())
				g.addEdge(positions[idv2], positions[idv1], positions[idv1].getDist(positions[idv2]));
			cout << 100.0 * id / 482568730 << " %" << endl;
		}
		g_file.close();
	}
	else
		cout << "Unable to open graph file";

	cout << "over" << endl;

	for (size_t i = 0; i < g.getVertexSet().size(); i++)
	{
		if (g.getVertexSet()[i]->getIndegree() >= 2)
			cout << g.getVertexSet()[i]->getIndegree() << endl;
	}

	
	return 0;
}
