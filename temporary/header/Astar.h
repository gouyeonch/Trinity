#pragma once
#include "moveStation.h"
#include "shareFunc.h"
#include <queue>
#include <cmath>
#include <algorithm>

#define INT_MAX 2147483647

void MiddleAstar(vector<string>name, vector<int>num, vector<int>line);
void printMin(vector < pair<vector<pair<Station*, int>>, Station*>> end_list);
int Astar(Station* start, Station* end);
double h(Station* a, Station* b);
void makeCenterMap();
void calCenter(vector<pair<Station*, int>>& list);
double calDistFromCenter(pair<double, double> stat);
void initVisit();

struct comp2
{
    bool operator()(Station* s1, Station* s2)
    {
        pair<double, double> a = make_pair(s1->alt, s1->lat);
        pair<double, double> b = make_pair(s2->alt, s2->lat);

        return calDistFromCenter(a) > calDistFromCenter(b);
    }
};

typedef struct Anode
{
	Station* ID;
	double F;
	int G;
	double H;
	Anode* parent;

	Anode(Station* ID, double F, int G, double H, Anode* parent)
	{
		this->ID = ID; this->F = F; this->G = G; this->H = H; this->parent = parent;
	}
}Anode;