#pragma once
#include <iostream>
#include <vector>
#define MAX 9
#define MAX_STAION 449

using namespace std;

typedef struct Station Station;
typedef unsigned long long W;
typedef struct Edge {
	int line;
	W weight;
	Station* next = NULL;
}Edge;

typedef struct Station {
	int line;
	vector<Edge*> ptr;
	string name;
	bool transfer = 0;
	int flag = 0;
	double alt;
	double lat;
	int visit = 0;
	W opt = ULLONG_MAX;
}Station;

