#pragma once
#include <iostream>
#include <vector>
//#define max 9

using namespace std;

typedef struct Station;
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
	int transfer = 0;
	int flag = 0;
}Station;

