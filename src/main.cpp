#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
#include "Graph.h"
#include "Position.h"
#include "Street.h"
#include "fileparser.h"
#include "menus.h"
#include "graphviewer.h"

using namespace std;

int main() {
	bool filesRead = false, coordsOK = false;
	double minx, miny, maxx, maxy;
	double userLatO = 0, userLongO = 0, userLatD = 0, userLongD = 0, accidentLat = 0, accidentLong = 0;
	Position *userO, *userD, *accident;
	Graph<Position> g;
	GraphViewer *gv;
	int id;
	int nodeX, nodeY;
	vector<Vertex<Position> *> vertexSet;

	int menu = 0;
	while (menu != 6) {
		menu = getMenu("Read files,Insert origin and destination,Add accident,Calculate path,View map,Exit");
		switch (menu) {
		case 1:
			readfiles(g, minx, miny, maxx, maxy);
			filesRead = true;
			break;
		case 2:
			if (filesRead) {
				cout << miny << ',' << maxy << ',' << minx << ',' << maxx << endl;
				cout << "Por favor insira as coordenadas da origem\n";
				while (userLatO < miny || userLatO > maxy || userLongO < minx || userLongO > maxx) {
					cout << "Introduza a latitude: \n";
					cin >> userLatO;
					cout << "Introduza a longitude: \n";
					cin >> userLongO;
				}

				system("cls");

				cout << "Por favor insira as coordenadas do destino\n";
				while (userLatD < miny || userLatD > maxy || userLongD < minx || userLongD > maxx) {
					cout << "Introduza a latitude: \n";
					cin >> userLatD;
					cout << "Introduza a longitude: \n";
					cin >> userLongD;
					system("cls");
				}

				userO = new Position(userLatO, userLongO);
				userD = new Position(userLatD, userLongD);

				//userO = new Position(41.17198, -8.594533);
				//userD = new Position(41.17221, -8.594659);

				if (g.getVertex(*userO) == NULL)
					cout << "coordenadas de origem nao existem\n";
				if (g.getVertex(*userD) == NULL)
					cout << "coordenadas de destino nao existem\n";
				if (g.getVertex(*userO) != NULL && g.getVertex(*userD) != NULL)
					coordsOK = true;
			}
			else
				cout << "must read files first!\n";
			system("pause");
			break;
		case 3:
			if (filesRead) {
				cout << "Por favor insira as coordenadas do acidente\n";
				while (accidentLat < miny || accidentLat > maxy || accidentLong < minx || accidentLong > maxx) {
					cout << "Introduza a latitude: \n";
					cin >> accidentLat;
					cout << "Introduza a longitude: \n";
					cin >> accidentLong;
					system("cls");
				}
				accident = new Position(accidentLat, accidentLong);

				if (g.getVertex(*accident) == NULL)
					cout << "coordenadas do acidente nao existem\n";
				else
					g.removeVertex(*accident);
			}
			else
				cout << "must read files first!\n";
			system("pause");
			break;
		case 4:
			if (filesRead && coordsOK) {
				g.dijkstraShortestPath(*userO);
				while (true) {
					cout << g.getVertex(*userD)->path->getInfo().getLatDeg() << ',' << g.getVertex(*userD)->path->getInfo().getLonDeg() << endl;
					*userD = g.getVertex(*userD)->path->getInfo();
				}
			}
			else
				cout << "must read files and add origin and destination first!\n";
			system("pause");
			break;
		case 5:
			if(filesRead) {
				gv = new GraphViewer(600, 600, false);

				gv->createWindow(600, 600);

				gv->defineEdgeColor("blue");
				gv->defineVertexColor("yellow");

				vertexSet = g.getVertexSet();
				cout << vertexSet.size() << endl;
				id = 0;

				while (!vertexSet.empty()) {
					id++;
					//gv->addNode(id, id+1, id+2);
					nodeX = 1000 * (vertexSet[0]->getInfo().getLonDeg() - miny) / (maxy - miny);
					nodeY = 1000 * (vertexSet[0]->getInfo().getLatDeg() - minx) / (maxx - minx);
					/*cout << vertexSet[0]->getInfo().getLonDeg() << ',' << miny << ',' << maxy << endl;
					cout << vertexSet[0]->getInfo().getLatDeg() << ',' << minx << ',' << maxx << endl;
					cout << nodeX << ',' << nodeY << endl;*/
					gv->addNode(id, nodeX, nodeY);
					vertexSet.erase(vertexSet.begin());
					gv->rearrange();
					//system("pause");
					}
			}
			else
				cout << "must read files first!\n";
			system("pause");
			break;
		}
	}
	return 0;
}
