#pragma once
#include "shareFunc.h"
#include <queue>

void MiddleSPFA(vector<string> name, vector<int> num, vector<int> line);
bool SPFA(map<Station*, W>& dist, int num, int line, string name);