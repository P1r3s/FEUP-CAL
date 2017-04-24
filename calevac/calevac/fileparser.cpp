#include "fileparser.h"

void readfiles(Graph<Position> &g, double &minx, double &miny, double &maxx, double &maxy) {
	int progressBarOld = -1;
	int progressBarNew = -1;
	map<unsigned long long, Position> positions;
	minx = numeric_limits<double>::max();
	miny = numeric_limits<double>::max();
	maxx = -numeric_limits<double>::max();
	maxy = -numeric_limits<double>::max();
	unsigned long long id;
	double lat, lon;
	Position *pos;
	string line, line2;
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
			positions.insert(pair<unsigned long long, Position>(id, *pos));

		}
		v_file.close();
	}
	else
		cout << "Unable to open vertex file";

	cout << "over" << endl;
	map<unsigned long long, Street> streets;
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
			streets.insert(pair<unsigned long long, Street>(id, *street));
		}
		e_file.close();
	}
	else
		cout << "Unable to open edge file";

	cout << "over" << endl;
	Vertex<Position> *v1, *v2;
	Edge<Position> *e;
	unsigned long long idv1, idv2;
	ifstream g_file("graph.txt");
	if (g_file.is_open()) {
		while (getline(g_file, line) && getline(g_file, line2)) {
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

			/*if (positions.count(idv1)) {
			g.addVertex(positions[idv1]);
			}

			if (positions.count(idv2)) {
			g.addVertex(positions[idv2]);
			}

			if (positions.count(idv1) && positions.count(idv2)) {
			g.addEdge(positions[idv1], positions[idv2], positions[idv1].getDist(positions[idv2]));
			if (streets[id].isTwoWay())
			g.addEdge(positions[idv2], positions[idv1], positions[idv1].getDist(positions[idv2]));
			}*/
			g.addVertex(positions[idv1]);
			g.addVertex(positions[idv2]);
			g.addEdge(positions[idv1], positions[idv2], 1);
			if (streets[id].isTwoWay())
				g.addEdge(positions[idv2], positions[idv1], 1);

			progressBarOld = progressBarNew;
			progressBarNew = 100 * id / 483715765;
			if (progressBarNew != progressBarOld || progressBarOld == -1) {
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n   \t\t\t\t\tPlease Wait";
				for (int i = 1; i < progressBarNew % 4 + 1; i++)
				{
					cout << '.';
				}
				cout << "\n\t\t\t\t\t[";
				for (int i = 0; i < progressBarNew / 5; i++) {
					cout << char(178);
				}
				for (int i = progressBarNew / 5; i < 20; i++) {
					cout << char(176);
				}
				cout << "] " << progressBarNew << "%\n";
			}
		}
		g_file.close();
	}
	else
		cout << "Unable to open graph file";
}