#pragma once
#include "edge.h"
#include <iostream>

using namespace std;

class Station {
private:
	string name;
	int line;
	Edge* edgePtr;
	int edgeNum;

public:
	Station();
	Station(string _name, int _line, int _edgeNum);
	void setEdge(Edge* edges);
	Edge* getEdge();
	void setLine(int _line);
	int getLine();
	void setName(string _name);
	string getName();
	void setEdgeNum(int _edgeNum);
	int getEdgeNum();
};