#pragma once
#include "station.h"

class Edge {
private:
	unsigned long long weight;
	Station station;
	int line;

public:
	Edge();
	Edge(int _line, unsigned long long _weight, Station& _station);
	unsigned long long getWeight();
	void setWeight(unsigned long long _weight);
	Station getStaion();
	void setStaion(Station& _station);
	int getLine();
	void setLine(int _line);
};