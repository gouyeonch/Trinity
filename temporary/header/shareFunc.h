#pragma once
#include "moveStation.h"
#include <map>

void reset();
Station* findStat(string name, int line);
void compareStation(map<Station*, W>* dist, unsigned int size);