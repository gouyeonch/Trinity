#pragma once
#include "shareFunc.h"
#include <queue>

map<Station*,W> dijkstra(int n,int l,string name);
void MiddleDijkstra(vector<string>name, vector<int>num, vector<int>line);

struct comp
{
    bool operator()(pair<Edge*, W>a, pair<Edge*, W>b)
    {
        return a.first->weight > b.first->weight;
    }
};
