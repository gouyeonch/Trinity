#pragma once
#include "dataStruct.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>

void tokenized(string str, int& line, string& name, W& weight, int& flag);
Station* allocStation(string str, W& weight, int& flag);
void swapStaion(Station*& n, Station*& current, Station*& N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag);
void lastStation(Station* n, Station* current, W nWeight);
void makeLine(Station*& s, vector<string> str);
void readFile(string num, vector<string>& vectorStr);