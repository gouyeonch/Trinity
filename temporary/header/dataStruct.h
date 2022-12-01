#pragma once
#include <iostream>
#include <vector>
//#define max 9

using namespace std;

<<<<<<< HEAD
typedef struct Station;
typedef unsigned long long W;

=======
typedef struct Station Station;
typedef unsigned long long W;
>>>>>>> gouyeonch
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
<<<<<<< HEAD
=======
	double alt;
	double lat;
	int visit = 0;
	W opt = 987654321;
>>>>>>> gouyeonch
}Station;

