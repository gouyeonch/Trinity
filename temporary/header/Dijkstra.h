#pragma once
#include "dataStruct.h"
#include "moveStation.h"
#include <queue>
#include <map>
#include <string>

map<Station*,W> dijkstra(int n,int l,string name);
void reset();
void DijkstraMiddle();