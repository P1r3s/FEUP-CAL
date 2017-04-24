#pragma once

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

void readfiles(Graph<Position> &g, double &minx, double &miny, double &maxx, double &maxy);