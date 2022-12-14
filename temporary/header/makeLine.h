#pragma once
#include "dataStruct.h"
#include "fileFunc.h"
#include <vector>
#include <string>
#include <stack>

void tokenized(string str, int& line, string& name, W& weight, int& flag);
Station* allocStation(string str, W& weight, int& flag);
Edge* allocEdge(int line, W weight, Station* station);
void swapStaion(Station*& n, Station*& current, Station*& N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag);
void middleStation(Station* n, Station* current, Station* N, W nWeight, W weight);
void lastStation(Station* n, Station* current, W nWeight);
void makeLine(Station*& s, vector<string> str);