#include "edge.h"
#include "station.h"

//Station method implement
Station::Station()
{
	name.clear();
	line = 0;
	edgePtr = NULL;
}

Station::Station(string _name, int _line, int _edgeNum)
{
	name = _name;
	line = _line;
	edgePtr = NULL;
	edgeNum = _edgeNum;
}

void Station::setEdge(Edge* edges)
{
	edgePtr = edges;
}

Edge* Station::getEdge()
{
	return edgePtr;
}

void Station::setLine(int _line)
{
	line = _line;
}

int Station::getLine()
{
	return line;
}

void Station::setName(string _name)
{
	name = _name;
}

string Station::getName()
{
	return name;
}

void Station::setEdgeNum(int _edgeNum)
{
	edgeNum = _edgeNum;
}

int Station::getEdgeNum()
{
	return edgeNum;
}

//Edge method implement
Edge::Edge()
{
	weight = 0;
	line = 0;
}

Edge::Edge(int _line, unsigned long long _weight, Station& _station)
{
	weight = _weight;
	station = _station;
	line = _line;
}

void Edge::setLine(int _line)
{
	line = _line;
}

int Edge::getLine()
{
	return line;
}

unsigned long long Edge::getWeight()
{
	return weight;
}

void Edge::setWeight(unsigned long long _weight)
{
	weight = _weight;
}


Station Edge::getStaion()
{
	return station;
}

void Edge::setStaion(Station& _station)
{
	station = _station;
}